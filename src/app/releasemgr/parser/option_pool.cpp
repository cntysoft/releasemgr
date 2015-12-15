//#include "option_pool.h"
//#include <QCommandLineParser>
//#include <QDebug>
//#include <QString>
//namespace releasemgr
//{

//OptionPool::OptionPool()
//{
//}

//OptionPool::OptionMapType& OptionPool::getEntryOptions()
//{
//   if(nullptr == m_entryOptions){
//      m_entryOptions = new OptionMapType
//      {
//      {"version", new QCommandLineOption("version", "the target version to build", "version")},
//      {"help", new QCommandLineOption("help", "print the help info")}
//   };
//   }
//   return *m_entryOptions;
//}

//OptionPool::OptionMapType& OptionPool::getFhzcOptions()
//{
//   if(nullptr == m_fhzcOptions){
//      m_fhzcOptions = new OptionMapType{
//      {"version", new QCommandLineOption("version", "the target version to build", "version")},
//      {"from", new QCommandLineOption("from", "the start version to build", "from")},
//      {"to", new QCommandLineOption("to", "the stop version to build", "to")},
//      {"aliyun", new QCommandLineOption("aliyun", "build for aliyun platform")}
//   };
//   }
//   return *m_fhzcOptions;
//}

//OptionPool::OptionMapType& OptionPool::getFhshopOptions()
//{
//   if(nullptr == m_fhshopOptions){
//      m_fhshopOptions = new OptionMapType{
//      {"version", new QCommandLineOption("version", "the target version to build", "version")},
//      {"from", new QCommandLineOption("from", "the start version to build", "from")},
//      {"to", new QCommandLineOption("to", "the stop version to build", "to")},
//      {"aliyun", new QCommandLineOption("aliyun", "build for aliyun platform")}
//   };
//   }
//   return *m_fhshopOptions;
//}

//OptionPool::OptionMapType& OptionPool::getRmMgrOptions()
//{
//   if(nullptr == m_rmmgrOptions){
//      m_rmmgrOptions = new OptionMapType{
//      {"projectDir", new QCommandLineOption("projectDir", "releasemgr project source files directory", "projectDir")},
//      {"buildDir", new QCommandLineOption("buildDir", "the working directory to build rpm package")},
//      {"version", new QCommandLineOption("version", "the target version to build", "version")},
//   };
//   }
//   return *m_rmmgrOptions;
//}

//QCommandLineParser* OptionPool::getEntryCmdParser()
//{
//   if(nullptr == m_entryCmdParser){
//      m_entryCmdParser = new QCommandLineParser();
//      OptionMapType map = getEntryOptions();
//      OptionMapType::const_iterator iterator = map.cbegin();
//      while(iterator != map.cend()){
//         m_entryCmdParser->addOption(*iterator.value());
//         iterator++;
//      }
//   }
//   return m_entryCmdParser;
//}

//QCommandLineParser* OptionPool::getFhzcCmdParser()
//{
//   if(nullptr == m_fhzcCmdParser){
//      m_fhzcCmdParser = new QCommandLineParser();
//      m_fhzcCmdParser->addPositionalArgument("action", "the build action type");
//      OptionMapType map = getFhzcOptions();
//      OptionMapType::const_iterator iterator = map.cbegin();
//      while(iterator != map.cend()){
//         m_fhzcCmdParser->addOption(*iterator.value());
//         iterator++;
//      }
//   }
//   return m_fhzcCmdParser;
//}

//QCommandLineParser* OptionPool::getFhshopCmdParser()
//{
//   if(nullptr == m_fhshopCmdParser){
//      m_fhshopCmdParser = new QCommandLineParser();
//      m_fhshopCmdParser->addPositionalArgument("action", "the build action type");
//      OptionMapType map = getFhzcOptions();
//      OptionMapType::const_iterator iterator = map.cbegin();
//      while(iterator != map.cend()){
//         m_fhshopCmdParser->addOption(*iterator.value());
//         iterator++;
//      }
//   }
//   return m_fhshopCmdParser;
//}

//QCommandLineParser* OptionPool::getRmMgrCmdParser()
//{
//   if(nullptr == m_rmmgrCmdParser){
//      m_rmmgrCmdParser = new QCommandLineParser();
//      m_rmmgrCmdParser->addPositionalArgument("action", "the build action type");
//      OptionMapType map = getRmMgrOptions();
//      OptionMapType::const_iterator iterator = map.cbegin();
//      while(iterator != map.cend()){
//         m_rmmgrCmdParser->addOption(*iterator.value());
//         iterator++;
//      }
//   }
//   return m_rmmgrCmdParser;
//}

//OptionPool::~OptionPool()
//{
//   if(nullptr != m_entryCmdParser){
//      delete m_entryCmdParser;
//   }
//   if(nullptr != m_fhzcCmdParser){
//      delete m_fhzcCmdParser;
//   }
//   if(nullptr != m_fhshopCmdParser){
//      delete m_fhshopCmdParser;
//   }
//   if(nullptr != m_rmmgrCmdParser){
//      delete m_rmmgrCmdParser;
//   }
//   if(nullptr != m_entryOptions){
//      OptionMapType::const_iterator it = m_entryOptions->cbegin();
//      while(it != m_entryOptions->cend()){
//         delete it.value();
//         it++;
//      }
//      delete m_entryOptions;
//   }
//   if(nullptr != m_fhzcOptions){
//      OptionMapType::const_iterator it = m_fhzcOptions->cbegin();
//      while(it != m_fhzcOptions->cend()){
//         delete it.value();
//         it++;
//      }
//      delete m_fhzcOptions;
//   }
//   if(nullptr != m_fhshopOptions){
//      OptionMapType::const_iterator it = m_fhzcOptions->cbegin();
//      while(it != m_fhshopOptions->cend()){
//         delete it.value();
//         it++;
//      }
//      delete m_fhshopOptions;
//   }
//   if(nullptr != m_rmmgrOptions){
//      OptionMapType::const_iterator it = m_rmmgrOptions->cbegin();
//      while(it != m_rmmgrOptions->cend()){
//         delete it.value();
//         it++;
//      }
//      delete m_rmmgrOptions;
//   }
//}

//}//releasemgr