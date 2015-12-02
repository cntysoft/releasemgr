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

#include "generate_diff_metainfo.h"
#include "task/abstract_taskmgr.h"
#include "kernel/errorinfo.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

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
      savedMetaInfo["modify"] << "Library/FengHuang/Version.php";
      savedMetaInfo["modify"] << "Library/FengHuang/DistConst.php";
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
   QDir releasemgrDir(m_buildDir+ds+"Library"+ds+"FengHuang"+ds+"ReleaseTools");
   if(releasemgrDir.exists()){
      releasemgrDir.removeRecursively();
   }
   if(m_needRunSenchaCmd){
      QStringList::const_iterator piterator = needRunCmdProjects.cbegin();
      while(piterator != needRunCmdProjects.cend()){
         QString projectName(*piterator);
         writeMsg(QString("正在打包sencha项目%1 ... ").arg(projectName).toLocal8Bit(), TerminalColor::LightYellow);
         
         //暂时不运行这段代码
         
         //execSenchaCmd(m_projectDir+ds+"PlatformJs"+ds+projectName);
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

}//diffbuild
}//fhzc
}//task
}//releasemgr