#include <QStringList>
#include <QDir>
#include <QChar>
#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSet>
#include <QSqlQuery>
#include <QMap>
#include <QVariant>
#include <QSetIterator>


#include "diff_build_tasks.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"
#include "utils/stddir.h"
#include "const.h"

namespace releasemgr{
namespace task{
namespace cloudcontrollerweb{
namespace diffbuild{

using sn::corelib::ErrorInfo;
using sn::corelib::Filesystem;

DiffBuildAbstractTask::DiffBuildAbstractTask(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :AbstractTask(taskmgr, invokeArgs),
     m_from(m_invokeArgs["from"]),
     m_to(m_invokeArgs["to"])
{
   m_buildDir = getSysCfgValue("webBuildDir").toString() + QDir::separator() + "cloudcontrollerweb_patch_" +  m_from +"_"+ m_to;
   m_projectDir = getSysCfgValue("webProjectDir").toString();
}

DiffBuildAbstractTask::~DiffBuildAbstractTask()
{}

Clear::Clear(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{
}

void Clear::exec()
{
   writeBeginMsg("清除相关打包文件夹内容 ... ");
   QDir buildDir(m_buildDir);
   if(buildDir.exists()){
      if(!buildDir.removeRecursively()){
         throw ErrorInfo("delete build directory failure");
      }
   }
   writeDoneMsg();
}

Clear::~Clear()
{}


GenerateDiffMetaInfo::GenerateDiffMetaInfo(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{}

void GenerateDiffMetaInfo::exec()
{
   writeBeginMsg("开始生成差异性元信息 ... ");
   QStringList modifiedSubmodules;
   SubmoduleHashMapType fromHashs;
   SubmoduleHashMapType toHashs;
   collectModifiedSubmodules(modifiedSubmodules, fromHashs, toHashs);
   GeneralKeyToListMapType modifiedFilenames;
   collectModifiedFiles(modifiedFilenames, modifiedSubmodules, fromHashs, toHashs);
   QStringList needRunCmdProjects;
   collectNeedRunCmdProjects(needRunCmdProjects, modifiedFilenames);
   GeneralKeyToListMapType savedMetaInfo;
   saveDiffMetaInfo(savedMetaInfo, modifiedFilenames, needRunCmdProjects);
   buildAndCopyFiles(savedMetaInfo, needRunCmdProjects);
   writeDoneMsg();
}

void GenerateDiffMetaInfo::collectModifiedSubmodules(QStringList& modifiedSubmodules, SubmoduleHashMapType& fromHashs, SubmoduleHashMapType& toHashs)
{
   writeMsg("\n开始分析改动的submodules数据 ... ", TerminalColor::LightYellow);
   //获取submodules路径
   QString baseName("submodules");
   QStringList submodulesCfgKeys = getChildKeys(baseName);
   QStringList submodulePaths;
   auto it = submodulesCfgKeys.cbegin();
   //获取submodule to submodule type map
   SubmoduleHashMapType submodulePathToTypeMap;
   while(it != submodulesCfgKeys.cend()){
      submodulePaths << getSysCfgValue(baseName+"/"+(*it)).toStringList();
      QStringList::const_iterator piterator = submodulePaths.cbegin();
      while(piterator != submodulePaths.cend()){
         submodulePathToTypeMap[*piterator] = *it;
         piterator++;
      }
      it++;
   }
   getSubmoduleHash(m_projectDir, m_from, submodulePaths, fromHashs);
   getSubmoduleHash(m_projectDir, m_to, submodulePaths, toHashs);
   //探测改变的submodule path
   SubmoduleHashMapType::const_iterator hashIterator = toHashs.cbegin();
   while(hashIterator != toHashs.cend()){
      if(fromHashs.contains(hashIterator.key())){
         if(hashIterator.value() != fromHashs[hashIterator.key()]){
            modifiedSubmodules << hashIterator.key();
         }
      }else{
         modifiedSubmodules << hashIterator.key();
      }
      hashIterator++;
   }
   
   QStringList::const_iterator miterator = modifiedSubmodules.cbegin();
   while(miterator != modifiedSubmodules.cend()){
      if(submodulePathToTypeMap[*miterator] == "sencha"){
         m_needRunSenchaCmd = true;
      }
      miterator++;
   }
   writeDoneMsg();
}

void GenerateDiffMetaInfo::collectModifiedFiles(GeneralKeyToListMapType& modifiedFiles, const QStringList& modifiedSubmodules, const SubmoduleHashMapType& fromHashs, const SubmoduleHashMapType& toHashs)
{
   writeMsg("正在分析主项目的差异性文件集合 ... ", TerminalColor::LightYellow);
   modifiedFiles["modify"] = QStringList();
   modifiedFiles["delete"] = QStringList();
   GeneralKeyToListMapType modifiedFilesMeta;
   getGitDiffFiles(m_projectDir, m_from, m_to, modifiedFilesMeta, QStringList(), 
   {"sql", "xml", "md", "properties", "gitignore", "scss"});
   //过滤相关不需要的路径
   GeneralKeyToListMapType::const_iterator modifyFileIterator = modifiedFilesMeta.cbegin();
   while(modifyFileIterator != modifiedFilesMeta.cend()){
      QStringList::const_iterator itemIterator = modifyFileIterator.value().cbegin();
      while(itemIterator != modifyFileIterator.value().cend()){
         if(!itemIterator->contains("UpgradeEnv") && !itemIterator->contains("ReleaseTools")){
            modifiedFiles[modifyFileIterator.key()] << *itemIterator;
         }
         itemIterator++;
      }
      modifyFileIterator++;
   }
   writeDoneMsg();
   //分析submodule里面的变动文件集合
   writeMsg("正在分析submodules的差异性文件集合 ... ", TerminalColor::LightYellow);
   QStringList::const_iterator submoduleIterator = modifiedSubmodules.cbegin();
   while(submoduleIterator != modifiedSubmodules.cend()){
      GeneralKeyToListMapType currentMeta;
      QString submodulePath = *submoduleIterator;
      getGitDiffFiles(m_projectDir+QDir::separator()+submodulePath, fromHashs[submodulePath], toHashs[submodulePath], currentMeta, QStringList(), 
      {"sql", "xml", "md", "properties", "gitignore", "scss"});
      GeneralKeyToListMapType::const_iterator submoduleMetaTypeIterator = currentMeta.cbegin();
      while(submoduleMetaTypeIterator != currentMeta.cend()){
         QStringList::const_iterator itemIterator = submoduleMetaTypeIterator.value().cbegin();
         while(itemIterator != submoduleMetaTypeIterator.value().cend()){
            modifiedFiles[submoduleMetaTypeIterator.key()] << *itemIterator;
            itemIterator++;
         }
         submoduleMetaTypeIterator++;
      }
      submoduleIterator++;
   }
   writeDoneMsg();
}

void GenerateDiffMetaInfo::collectNeedRunCmdProjects(QStringList& projects, const GeneralKeyToListMapType& modifiedFilenames)
{
   writeMsg("开始分析需要执行sencha cmd命令项目集合 ... ", TerminalColor::LightYellow);
   //获取sencha项目的所有文件集合
   GeneralKeyToListMapType senchaProjectFilenames;
   QString submoduleProjectKey("senchaProjects");
   QStringList senchaProjectKeys = getChildKeys(submoduleProjectKey);
   QStringList::const_iterator senchaKeyIterator = senchaProjectKeys.cbegin();
   while(senchaKeyIterator != senchaProjectKeys.cend()){
      QString pkey(*senchaKeyIterator);
      if(!senchaProjectFilenames.contains(pkey)){
         senchaProjectFilenames[pkey] = QStringList();
      }
      QStringList projectFilepaths = getSysCfgValue(submoduleProjectKey+'/'+pkey).toStringList();
      QStringList::const_iterator ppIterator = projectFilepaths.cbegin();
      while(ppIterator != projectFilepaths.cend()){
         QString path = m_projectDir +QDir::separator()+ (*ppIterator);
         QFileInfo pathInfo(path);
         if(pathInfo.isFile()){
            senchaProjectFilenames[pkey] << path;
         }else if(pathInfo.isDir()){
            Filesystem::traverseFs(path, 0, [&senchaProjectFilenames, &pkey](QFileInfo& fileInfo, int){
               if(fileInfo.isFile()){
                  senchaProjectFilenames[pkey] << fileInfo.absoluteFilePath();
               }
            });
         }
         ppIterator++;
      }
      senchaKeyIterator++;
   }
   GeneralKeyToListMapType::const_iterator mfiterator = modifiedFilenames.cbegin();
   while(mfiterator != modifiedFilenames.cend()){
      QStringList filePathnames = mfiterator.value();
      QStringList::const_iterator fpIterator = filePathnames.cbegin();
      while(fpIterator != filePathnames.cend()){
         GeneralKeyToListMapType::const_iterator spfiterator = senchaProjectFilenames.cbegin();
         while(spfiterator != senchaProjectFilenames.cend()){
            if(spfiterator.value().contains(*fpIterator)){
               m_needRunSenchaCmd = true;
               if(!projects.contains(spfiterator.key())){
                  projects << spfiterator.key();
               }
            }
            spfiterator++;
         }
         fpIterator++;
      }
      mfiterator++;
   }
   writeDoneMsg();
}

void GenerateDiffMetaInfo::saveDiffMetaInfo(GeneralKeyToListMapType& savedMetaInfo, const GeneralKeyToListMapType &modifiedFiles, const QStringList& needRunCmdProjects)
{
   writeMsg("正在保存生成的元信息数据 ... ", TerminalColor::LightYellow);
   if(!modifiedFiles["delete"].isEmpty() || !modifiedFiles["modify"].isEmpty()){
      GeneralKeyToListMapType::const_iterator typeIterator = modifiedFiles.cbegin();
      while(typeIterator != modifiedFiles.cend()){
         savedMetaInfo[typeIterator.key()] = QStringList();
         QStringList::const_iterator itemIterator = typeIterator.value().cbegin();
         while(itemIterator != typeIterator.value().cend()){
            QString relative(*itemIterator);
            relative.replace(m_projectDir+QDir::separator(), "");
            if(!relative.startsWith("PlatformJs") && !relative.startsWith("Config")){
               savedMetaInfo[typeIterator.key()] << relative;
            }
            itemIterator++;
         }
         typeIterator++;
      }
      //强行加入版本文件，因为版本文件肯定每次都变化，但是却很特殊
      savedMetaInfo["modify"] << "Library/CloudController/Version.php";
      savedMetaInfo["modify"] << "Library/CloudController/DistConst.php";
   }
   savedMetaInfo["senchaChangedProjects"] = needRunCmdProjects;
   //生成json数据
   QJsonDocument jsonDoc;
   QJsonObject jsonObject;
   GeneralKeyToListMapType::const_iterator smifiTerator = savedMetaInfo.cbegin();
   while(smifiTerator != savedMetaInfo.cend()){
      QJsonArray jsonArray;
      QStringList items(smifiTerator.value());
      QStringList::const_iterator itemIterator = items.cbegin();
      while(itemIterator != items.cend()){
         jsonArray.append(QJsonValue(*itemIterator));
         itemIterator++;
      }
      jsonObject.insert(smifiTerator.key(), QJsonValue(jsonArray));
      smifiTerator++;
   }
   QChar ds = QDir::separator();
   jsonDoc.setObject(jsonObject);
   Filesystem::filePutContents(m_buildDir+ds+m_from+"_"+m_to+".json", jsonDoc.toJson());
   writeDoneMsg();
}

void GenerateDiffMetaInfo::buildAndCopyFiles(const GeneralKeyToListMapType& savedMetaInfo, const QStringList& needRunCmdProjects)
{
   //复制相关的变化文件
   writeMsg("复制相关的变化文件到打包文件夹 ... ", TerminalColor::LightYellow);
   QStringList::const_iterator mdfiterator = savedMetaInfo["modify"].cbegin();
   QChar ds(QDir::separator());
   while(mdfiterator != savedMetaInfo["modify"].cend()){
      QString relative(*mdfiterator);
      Filesystem::copyFile(m_projectDir+ds+relative, m_buildDir+ds+relative);
      mdfiterator++;
   }
   writeDoneMsg();
   //删除源码库里面跟打包相关的代码
   QDir releasemgrDir(m_buildDir+ds+"Library"+ds+"CloudController"+ds+"ReleaseTools");
   if(releasemgrDir.exists()){
      releasemgrDir.removeRecursively();
   }
   if(m_needRunSenchaCmd){
      QStringList::const_iterator piterator = needRunCmdProjects.cbegin();
      while(piterator != needRunCmdProjects.cend()){
         QString projectName(*piterator);
         writeMsg(QString("正在打包sencha项目%1 ... ").arg(projectName).toLocal8Bit(), TerminalColor::LightYellow);
         //暂时不运行这段代码
         execSenchaCmd(m_projectDir+ds+"PlatformJs"+ds+projectName);
         writeDoneMsg();
         piterator++;
      }
      //复制打包结果
      writeMsg("正在复制打包结果文件 ... ", TerminalColor::LightYellow);
      QString sourceDir(m_projectDir+ds+"PlatformJs"+ds+"build"+ds+"production");
      Filesystem::traverseFs(sourceDir, 0, [this](QFileInfo& fileInfo, int){
         if(fileInfo.isFile()){
            QString sourceFilename(fileInfo.absoluteFilePath());
            QString destinationFilename(sourceFilename);
            destinationFilename.replace(this->m_projectDir, this->m_buildDir);
            Filesystem::copyFile(sourceFilename, destinationFilename);
         }
      });
      writeDoneMsg();
   }
}

void GenerateDiffMetaInfo::getSubmoduleHash(const QString &projectDir, const QString &versionTag, const QStringList &submodules, SubmoduleHashMapType &hashs)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(projectDir);
   args << "ls-tree" << versionTag << submodules;
   process.start("git", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.errorString());
   }
   QString ret(process.readAll());
   auto lines = ret.split("\n", QString::SkipEmptyParts);
   auto lineIterator = lines.cbegin();
   while(lineIterator != lines.cend()){
      auto parts = (*lineIterator).split(QRegularExpression("\\s"));
      hashs[parts[3]] = parts[2];
      lineIterator++;
   }
}

void GenerateDiffMetaInfo::getGitDiffFiles(const QString &projectDir, const QString &from, const QString &to, GeneralKeyToListMapType& modifiedFilesMap, const QStringList &paths, const QStringList &skips)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(projectDir);
   args << "diff" << "--name-only" << from << to;
   if(!paths.isEmpty()){
      args << "--" << paths;
   }
   process.start("git", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.errorString());
   }
   QString ret(process.readAll());
   QStringList lines = ret.split('\n', QString::SkipEmptyParts);
   QStringList modifiedFilenames;
   QStringList deletedFilenames;
   QStringList::const_iterator lineIterator = lines.cbegin();
   while(lineIterator != lines.cend()){
      QString filename((*lineIterator).trimmed());
      if(filename.contains(".sencha")){
         continue;
      }
      QString filePathname = projectDir+QDir::separator()+filename;
      QFileInfo fileInfo(filePathname);
      if(fileInfo.exists()){
         if(fileInfo.isFile() && !skips.contains(fileInfo.suffix())){
            //增加修改都放在一起
            modifiedFilenames << filePathname;
         }
      }else{
         if(fileInfo.suffix() != ""){
            deletedFilenames << filePathname;
         }
      }
      lineIterator++;
   }
   modifiedFilesMap["modify"] = modifiedFilenames;
   modifiedFilesMap["delete"] = deletedFilenames;
}

void GenerateDiffMetaInfo::execSenchaCmd(const QString &projectDir)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(projectDir);
   args << "app" << "build";
   process.start("sencha", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.errorString());
   }
}

GenerateDiffMetaInfo::~GenerateDiffMetaInfo()
{}

GenerateVersionInfo::GenerateVersionInfo(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{}

void GenerateVersionInfo::exec()
{
   writeBeginMsg("正在生成版本文件 ... ");
   QChar ds = QDir::separator();
   QFile versionTplFile(m_buildDir+ds+"Library"+ds+"CloudController"+ds+"Version.php");
   versionTplFile.open(QFile::ReadWrite);
   QByteArray content = versionTplFile.readAll();
   content.replace("{version}", m_invokeArgs["to"].toLatin1());
   versionTplFile.remove();
   QFile versionFile(m_buildDir+ds+"Library"+ds+"CloudController"+ds+"Version.php");
   versionFile.open(QFile::WriteOnly|QFile::Truncate);
   versionFile.write(content);
   writeDoneMsg();
}

GenerateVersionInfo::~GenerateVersionInfo()
{}

SetupDistConst::SetupDistConst(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{}

void SetupDistConst::exec()
{
   writeBeginMsg("正在生成部署相关的常量 ... ");
   bool deployForAliyun = m_invokeArgs["aliyun"] == "true" ? true : false;
   QChar ds = QDir::separator();
   QString baseDir(StdDir::getAssetsDir()+ds+"cloudcontroller"+ds+"distconst");
   QString constFilename;
   if(deployForAliyun){
      constFilename = baseDir + ds + "AliyunDeployment.php";
   }else{
      constFilename = baseDir + ds + "NormalDeployment.php";
   }
   QString targetConstFilename = m_buildDir + ds + "Library" + ds + "CloudController" + ds + "DistConst.php";
   Filesystem::copyFile(constFilename, targetConstFilename, true);
   writeDoneMsg();
}

SetupDistConst::~SetupDistConst()
{}

AnalysisDatabase::AnalysisDatabase(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs),
     m_fromDb(QSqlDatabase::addDatabase("QMYSQL", QLatin1String("FromDb"))),
     m_toDb(QSqlDatabase::addDatabase("QMYSQL", QLatin1String("ToDb")))
{ 
}

void AnalysisDatabase::exec()
{
   writeBeginMsg("正在分析数据库结构 ... ");
   openDatabases();
   QJsonDocument metaJsonDoc;
   QJsonObject typeItemJsonObject;
   writeMsg("\n正在分析数据库表级别差异 ... ", TerminalColor::LightYellow);
   QSet<QString> fromTableNameSet(m_fromDb.tables().toSet());
   QSet<QString> toTableNameSet(m_toDb.tables().toSet());
   QSet<QString> deleteTableNameSet(fromTableNameSet - toTableNameSet);
   QSet<QString> newTableNameSet(toTableNameSet - fromTableNameSet);
   
   //设置删除生成json对象
   QJsonArray deleteTableNameJsonArray;
   QSetIterator<QString> tableSetIterator(deleteTableNameSet);
   while(tableSetIterator.hasNext()){
      deleteTableNameJsonArray.append(QJsonValue(tableSetIterator.next()));
   }
   
   QJsonArray newTableNameJsonArray;
   tableSetIterator = newTableNameSet;
   while(tableSetIterator.hasNext()){
      newTableNameJsonArray.append(QJsonValue(tableSetIterator.next()));
   }
   
   if(!deleteTableNameJsonArray.isEmpty()){
      typeItemJsonObject.insert("deleted", QJsonValue(deleteTableNameJsonArray));
   }
   if(!newTableNameJsonArray.isEmpty()){
      typeItemJsonObject.insert("new", QJsonValue(newTableNameJsonArray));
   }
   writeDoneMsg();
   
   QSet<QString> intersection(toTableNameSet);
   intersection.intersect(fromTableNameSet);
   writeMsg("正在分析数据库字段级别差异性 ... ", TerminalColor::LightYellow);
   QJsonObject modifyTableJsonObject;
   //探测修改表信息
   QSet<QString>::const_iterator itableIterator = intersection.cbegin();
   while(itableIterator != intersection.cend()){
      QJsonObject tableColModifyMeta;
      QString tableName(*itableIterator);
      writeMsg(QString("\n正在分析数据表%1字段 ... ").arg(tableName).toLocal8Bit(), TerminalColor::LightBlue);
      ColItemsType fromFields = getTableColumns(m_fromDb.databaseName(), tableName);
      ColItemsType toFields = getTableColumns(m_toDb.databaseName(), tableName);
      QSet<QString> fromFieldNames(fromFields.keys().toSet());
      //探测全新创建的和删除的col，这两个比较简单
      QSet<QString> toFieldNames(toFields.keys().toSet());
      QSet<QString> deleteTableColsSet(fromFieldNames - toFieldNames);
      QSet<QString> newTableColsSet(toFieldNames - fromFieldNames);
      
      QJsonArray deleteTableColsJsonArray;
      QSetIterator<QString> colSetIterator(deleteTableColsSet);
      while(colSetIterator.hasNext()){
         deleteTableColsJsonArray.append(QJsonValue(colSetIterator.next()));
      }
      
      QJsonArray newTableColsJsonArray;
      colSetIterator = newTableColsSet;
      while(colSetIterator.hasNext()){
         newTableColsJsonArray.append(QJsonValue(colSetIterator.next()));
      }
      if(!newTableColsJsonArray.isEmpty()){
         tableColModifyMeta.insert("new", QJsonValue(newTableColsJsonArray));
      }
      
      if(!deleteTableColsJsonArray.isEmpty()){
         tableColModifyMeta.insert("delete", QJsonValue(deleteTableColsJsonArray));
      }
      
      //探测修改的cols这个比较麻烦
      QSet<QString> modifyTableColsSet = toFieldNames;
      modifyTableColsSet.intersect(fromFieldNames);
      QJsonObject modifyTableColJsonMeta;
      colSetIterator = modifyTableColsSet;
      while(colSetIterator.hasNext()){
         QString colName(colSetIterator.next());
         ColMetaType fromColMeta(fromFields[colName]);
         ColMetaType toColMeta(toFields[colName]);
         if(fromColMeta["column_default"] != toColMeta["column_default"] ||
               fromColMeta["is_nullable"] != toColMeta["is_nullable"] ||
               fromColMeta["data_type"] != toColMeta["data_type"] ||
               fromColMeta["character_maximum_length"] != toColMeta["character_maximum_length"] ||
               fromColMeta["character_octet_length"] != toColMeta["character_octet_length"] ||
               fromColMeta["numeric_precision"] != toColMeta["numeric_precision"] ||
               fromColMeta["numeric_scale"] != toColMeta["numeric_scale"] ||
               fromColMeta["numeric_unsigned"] != toColMeta["numeric_unsigned"]){
            QJsonObject colModifyItemJsonObject;
            QJsonObject colModifyItemFromMetaJsonObject;
            QJsonObject colModifyItemJsonToMetaObject;
            
            colModifyItemFromMetaJsonObject.insert("column_default", QJsonValue(fromColMeta["column_default"].toString()));
            colModifyItemFromMetaJsonObject.insert("is_nullable", QJsonValue(fromColMeta["is_nullable"].toBool()));
            colModifyItemFromMetaJsonObject.insert("data_type", QJsonValue(fromColMeta["data_type"].toString()));
            colModifyItemFromMetaJsonObject.insert("character_maximum_length", QJsonValue(fromColMeta["character_maximum_length"].toString()));
            colModifyItemFromMetaJsonObject.insert("character_octet_length", QJsonValue(fromColMeta["character_octet_length"].toString()));
            colModifyItemFromMetaJsonObject.insert("numeric_precision", QJsonValue(fromColMeta["numeric_precision"].toString()));
            colModifyItemFromMetaJsonObject.insert("numeric_scale", QJsonValue(fromColMeta["numeric_scale"].toString()));
            colModifyItemFromMetaJsonObject.insert("numeric_unsigned", QJsonValue(fromColMeta["numeric_unsigned"].toString()));
            
            colModifyItemJsonToMetaObject.insert("column_default", QJsonValue(toColMeta["column_default"].toString()));
            colModifyItemJsonToMetaObject.insert("is_nullable", QJsonValue(toColMeta["is_nullable"].toBool()));
            colModifyItemJsonToMetaObject.insert("data_type", QJsonValue(toColMeta["data_type"].toString()));
            colModifyItemJsonToMetaObject.insert("character_maximum_length", QJsonValue(toColMeta["character_maximum_length"].toString()));
            colModifyItemJsonToMetaObject.insert("character_octet_length", QJsonValue(toColMeta["character_octet_length"].toString()));
            colModifyItemJsonToMetaObject.insert("numeric_precision", QJsonValue(toColMeta["numeric_precision"].toString()));
            colModifyItemJsonToMetaObject.insert("numeric_scale", QJsonValue(toColMeta["numeric_scale"].toString()));
            colModifyItemJsonToMetaObject.insert("numeric_unsigned", QJsonValue(toColMeta["numeric_unsigned"].toString()));
            
            colModifyItemJsonObject.insert("from", QJsonValue(colModifyItemFromMetaJsonObject));
            colModifyItemJsonObject.insert("to", QJsonValue(colModifyItemJsonToMetaObject));
            modifyTableColJsonMeta.insert(colName, QJsonValue(colModifyItemJsonObject));
            tableColModifyMeta.insert("modify", QJsonValue(modifyTableColJsonMeta));
         }
      }
      
      if(tableColModifyMeta.contains("new") || tableColModifyMeta.contains("delete") || tableColModifyMeta.contains("modify")){
         modifyTableJsonObject.insert(tableName, QJsonValue(tableColModifyMeta));
      }
      writeMsg(" done", TerminalColor::Green);
      itableIterator++;
   }
   
   typeItemJsonObject.insert("modify", modifyTableJsonObject);
   writeMsg("\n");
   metaJsonDoc.setObject(typeItemJsonObject);
   writeBeginMsg("正在保存分析结果数据 ... ");
   Filesystem::filePutContents(m_buildDir+QDir::separator()+"dbmeta_"+m_from+"_"+m_to+".json", metaJsonDoc.toJson());
   writeDoneMsg();
}

void AnalysisDatabase::openDatabases()
{
   QString host = m_settings.getValue("db.host", CFG_GROUP_GLOBAL).toString();
   QString username = m_settings.getValue("db.username", CFG_GROUP_GLOBAL).toString();
   QString password = m_settings.getValue("db.password", CFG_GROUP_GLOBAL).toString();
   QString baseDbName = "cloudcontroller_";
   if(!m_toDb.isOpen()){
      m_toDb.setHostName(host);
      m_toDb.setUserName(username);
      m_toDb.setPassword(password);
      m_toDb.setDatabaseName(baseDbName+m_to);
      if(!m_toDb.open()){
         throw ErrorInfo(m_toDb.lastError().text());
      }
   }
   if(!m_fromDb.isOpen()){
      m_fromDb.setHostName(host);
      m_fromDb.setUserName(username);
      m_fromDb.setPassword(password);
      m_fromDb.setDatabaseName(baseDbName+m_from);
      if(!m_fromDb.open()){
         throw ErrorInfo(m_fromDb.lastError().text());
      }
   }
   
}

AnalysisDatabase::ColItemsType AnalysisDatabase::getTableColumns(const QString& schema, const QString& tableName)
{
   QString sql("SELECT `C`.`ORDINAL_POSITION`, `C`.`COLUMN_DEFAULT`, `C`.`IS_NULLABLE`,"
               "`C`.`DATA_TYPE`, `C`.`CHARACTER_MAXIMUM_LENGTH`, `C`.`CHARACTER_OCTET_LENGTH`,"
               "`C`.`NUMERIC_PRECISION`, `C`.`NUMERIC_SCALE`, `C`.`COLUMN_NAME`, `C`.`COLUMN_TYPE` "
               "FROM `INFORMATION_SCHEMA`.`TABLES`  T "
               "INNER JOIN `INFORMATION_SCHEMA`.`COLUMNS`  C "
               "ON `T`.`TABLE_SCHEMA` = `C`.`TABLE_SCHEMA` "
               "AND `T`.`TABLE_NAME` = `C`.`TABLE_NAME` "
               "WHERE `T`.`TABLE_TYPE` IN (\'BASE TABLE\', \'VIEW\') "
               "AND `T`.`TABLE_NAME` = \'%1\' "
               "AND `T`.`TABLE_SCHEMA` = \'%2\'");
   sql = sql.arg(tableName, schema);
   QSqlQuery query;
   if(m_fromDb.databaseName() == schema){
      query = m_fromDb.exec(sql);
   }else{
      query = m_toDb.exec(sql);
   }
   ColItemsType cols;
   while(query.next()){
      ColMetaType meta{
         {"ordinal_position", query.value("ORDINAL_POSITION")},
         {"column_default", query.value("COLUMN_DEFAULT")},
         {"is_nullable", QVariant(query.value("IS_NULLABLE").toString() == "YES")},
         {"data_type", query.value("DATA_TYPE")},
         {"character_maximum_length", query.value("CHARACTER_MAXIMUM_LENGTH")},
         {"character_octet_length", query.value("CHARACTER_OCTET_LENGTH")},
         {"numeric_precision", query.value("NUMERIC_PRECISION")},
         {"numeric_scale", query.value("NUMERIC_SCALE")},
         {"numeric_unsigned", QVariant(query.value("COLUMN_TYPE").toString().contains("unsigned"))}
      };
      cols.insert(query.value("COLUMN_NAME").toString(), meta);
   }
   return cols;
}

AnalysisDatabase::~AnalysisDatabase()
{}

CopyUpgradeScript::CopyUpgradeScript(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   : DiffBuildAbstractTask(taskmgr, invokeArgs)
{
}

void CopyUpgradeScript::exec()
{
   writeBeginMsg("正在复制升级脚本文件 ... ");
   QString sourceFilename(m_projectDir+DS+"UpgradeEnv"+DS+"Scripts"+DS+"upgradescript_"+
                          m_from+"_"+m_to+".js");
   QString destinationFilename(sourceFilename);
   destinationFilename.replace(m_projectDir+DS+"UpgradeEnv"+DS+"Scripts", m_buildDir);
   if(QFileInfo(sourceFilename).exists()){
      Filesystem::copyFile(sourceFilename, destinationFilename);
   }
   writeDoneMsg();
}

CopyUpgradeScript::~CopyUpgradeScript()
{}

Compress::Compress(const AbstractTaskMgr &taskmgr, const TaskParamsType &invokeArgs)
   :DiffBuildAbstractTask(taskmgr, invokeArgs)
{
}

void Compress::exec()
{
   writeBeginMsg("开始压缩项目文件 ... ");
   QString sourceDirName = QString("cloudcontrollerweb_patch_%1_%2").arg(m_from, m_to);
   execGzipCmd(sourceDirName+".tar.gz", sourceDirName);
   writeDoneMsg();
}
void Compress::execGzipCmd(const QString& savedFilename, const QString &sourceDir)
{
   QProcess process;
   QStringList args;
   process.setWorkingDirectory(QFileInfo(m_buildDir).absolutePath());
   args << "-czvf" << savedFilename << sourceDir;
   process.start("tar", args);
   bool status = process.waitForFinished(-1);
   if(!status || process.exitCode() != 0){
      throw ErrorInfo(process.errorString());
   }
}

Compress::~Compress()
{}

}//diffbuild
}//cloudcontrollerweb
}//task
}//releasemgr