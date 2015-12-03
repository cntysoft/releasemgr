#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QSet>
#include <QSqlQuery>
#include <QDir>
#include <QMap>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QSetIterator>

#include "analysis_database.h"
#include "task/abstract_taskmgr.h"
#include "settings.h"
#include "io/filesystem.h"

namespace releasemgr{
namespace task{
namespace fhzc{
namespace diffbuild{

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
            
            colModifyItemJsonToMetaObject.insert("column_default", QJsonValue(fromColMeta["column_default"].toString()));
            colModifyItemJsonToMetaObject.insert("is_nullable", QJsonValue(fromColMeta["is_nullable"].toBool()));
            colModifyItemJsonToMetaObject.insert("data_type", QJsonValue(fromColMeta["data_type"].toString()));
            colModifyItemJsonToMetaObject.insert("character_maximum_length", QJsonValue(fromColMeta["character_maximum_length"].toString()));
            colModifyItemJsonToMetaObject.insert("character_octet_length", QJsonValue(fromColMeta["character_octet_length"].toString()));
            colModifyItemJsonToMetaObject.insert("numeric_precision", QJsonValue(fromColMeta["numeric_precision"].toString()));
            colModifyItemJsonToMetaObject.insert("numeric_scale", QJsonValue(fromColMeta["numeric_scale"].toString()));
            colModifyItemJsonToMetaObject.insert("numeric_unsigned", QJsonValue(fromColMeta["numeric_unsigned"].toString()));
            
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
   QString host = m_settings.getValue("db.host", CFG_GROUP_GLOABL).toString();
   QString username = m_settings.getValue("db.username", CFG_GROUP_GLOABL).toString();
   QString password = m_settings.getValue("db.password", CFG_GROUP_GLOABL).toString();
   QString baseDbName = "fenghuang_";
   if(!m_toDb.isOpen()){
      m_toDb.setHostName(host);
      m_toDb.setUserName(username);
      m_toDb.setPassword(password);
      m_toDb.setDatabaseName(baseDbName+m_to);
      m_toDb.open();
   }
   if(!m_fromDb.isOpen()){
      m_fromDb.setHostName(host);
      m_fromDb.setUserName(username);
      m_fromDb.setPassword(password);
      m_fromDb.setDatabaseName(baseDbName+m_from);
      m_fromDb.open();
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

}//diffbuild
}//fhzc
}//task
}//releasemgr
