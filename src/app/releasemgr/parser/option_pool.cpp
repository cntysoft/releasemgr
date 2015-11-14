#include "option_pool.h"
#include <QCommandLineParser>
#include <QDebug>
#include <QString>
namespace releasemgr
{

OptionPool::OptionPool()
{
}

OptionPool::OptionMapType& OptionPool::getFhzcOptions()
{
   if(nullptr == fhzcOptions){
      fhzcOptions = new OptionMapType{
         {"version", new QCommandLineOption("version", "the target version to build", "version")},
         {"targetdeploytype", new QCommandLineOption("targetdeploytype", "the target deploy type code", "targetdeploytype")},
      };
   }
   return *fhzcOptions;
}

OptionPool::OptionMapType& OptionPool::getEntryOptions()
{
   if(nullptr == entryOptions){
      entryOptions = new OptionMapType
      {
         {"version", new QCommandLineOption("version", "the target version to build", "version")},
         {"help", new QCommandLineOption("help", "print the help info")}
      };
   }
   return *entryOptions;
}

QCommandLineParser* OptionPool::getEntryCmdParser()
{
   if(nullptr == entryCmdParser){
      entryCmdParser = new QCommandLineParser();
      OptionMapType map = getEntryOptions();
      OptionMapType::const_iterator iterator = map.cbegin();
      while(iterator != map.cend()){
         entryCmdParser->addOption(*iterator.value());
         iterator++;
      }
   }
   return entryCmdParser;
}

QCommandLineParser* OptionPool::getFhzcCmdParser()
{
   if(nullptr == fhzcCmdParser){
      fhzcCmdParser = new QCommandLineParser();
      fhzcCmdParser->addPositionalArgument("action", "the build action type");
      OptionMapType map = getFhzcOptions();
      OptionMapType::const_iterator iterator = map.cbegin();
      while(iterator != map.cend()){
         fhzcCmdParser->addOption(*iterator.value());
         iterator++;
      }
   }
   return fhzcCmdParser;
}

 
}//releasemgr