#include "command_runner.h"
#include "application.h"
#include "kernel/errorinfo.h"
#include "io/terminal.h"
#include "command/abstract_command.h"
#include "command/command_meta.h"
#include "command/command_repo.h"

namespace releasemgr
{

using sn::corelib::ErrorInfo;
using sn::corelib::TerminalColor;
using sn::corelib::CommandMeta;
using sn::corelib::AbstractCommand;

using releasemgr::command::GlobalVersionCommand;
using releasemgr::command::GlobalHelpCommand;
using releasemgr::command::FhzcBuildCommand;
using releasemgr::command::RmMgrBuildCommand;
using releasemgr::command::FhshopBuildCommand;
using releasemgr::command::UpgrademgrBuildCommand;
using releasemgr::command::CloudControllerBuildCommand;
using releasemgr::command::DeploySystemBuildCommand;
using releasemgr::command::ZhuChaoBuildCommand;

CommandRunner::CommandRunner(Application &app)
   : BaseCommandRunner(app)
{
   initUsageText();
   initCommandPool();
   initRouteItems();
}

void CommandRunner::initUsageText()
{
   addUsageText("welcome to use sheneninfo release manager system\n\n", TerminalColor::Green);
   addUsageText("usage: \n\n", TerminalColor::LightBlue);
   addUsageText("--version  print main system version number\n");
   addUsageText("--help     print help document\n\n");
   addUsageText("releasemgr zhuchao webfullbuild --version=<version> [--aliyun]\n");
   addUsageText("releasemgr zhuchao webdiffbuild --from=<start version> --to=<to version> [--aliyun]\n");
   addUsageText("releasemgr rmmgr rpmbuild [--projectDir=<projectDir>] [--buildDir=<buildDir>] --version=<version to build>\n");
   addUsageText("releasemgr upgrademgrmaster rpmbuild [--projectDir=<projectDir>] [--buildDir=<buildDir>] --version=<version to build>\n");
   addUsageText("releasemgr upgrademgrslave rpmbuild [--projectDir=<projectDir>] [--buildDir=<buildDir>] --version=<version to build>\n");
   addUsageText("releasemgr cloudcontroller rpmbuild [--projectDir=<projectDir>] [--buildDir=<buildDir>] --version=<version to build>\n");
   addUsageText("releasemgr cloudcontroller webfullbuild --version=<version> [--aliyun]\n");
   addUsageText("releasemgr cloudcontroller webdiffbuild --from=<start version> --to=<stop version> [--aliyun]\n");
   addUsageText("releasemgr deploysystem metaserver rpmbuild [--projectDir=<projectDir>] [--buildDir=<buildDir>] --version=<version to build>\n");
   addUsageText("releasemgr deploysystem luoxi rpmbuild [--projectDir=<projectDir>] [--buildDir=<buildDir>] --version=<version to build>\n");
}

void CommandRunner::initCommandPool()
{
   m_cmdRegisterPool.insert("Global_Version", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      GlobalVersionCommand* cmd = new GlobalVersionCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
   m_cmdRegisterPool.insert("Global_Help", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      GlobalHelpCommand* cmd = new GlobalHelpCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
//   m_cmdRegisterPool.insert("Fhzc_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
//      FhzcBuildCommand* cmd = new FhzcBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
//      return cmd;
//   });
//   m_cmdRegisterPool.insert("Fhshop_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
//      FhshopBuildCommand* cmd = new FhshopBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
//      return cmd;
//   });
   m_cmdRegisterPool.insert("RmMgr_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      RmMgrBuildCommand* cmd = new RmMgrBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
   m_cmdRegisterPool.insert("Upgrademgr_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      UpgrademgrBuildCommand* cmd = new UpgrademgrBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
   m_cmdRegisterPool.insert("CloudController_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      CloudControllerBuildCommand* cmd = new CloudControllerBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
   m_cmdRegisterPool.insert("DeploySystem_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      DeploySystemBuildCommand* cmd = new DeploySystemBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
   m_cmdRegisterPool.insert("ZhuChao_Build", [](AbstractCommandRunner& runner, const CommandMeta& meta)->AbstractCommand*{
      ZhuChaoBuildCommand* cmd = new ZhuChaoBuildCommand(dynamic_cast<CommandRunner&>(runner), meta);
      return cmd;
   });
}

void CommandRunner::initRouteItems()
{
   addCmdRoute("version", "--version", 1, {
                  {"category", "Global"},
                  {"name", "Version"}
               });
   addCmdRoute("help", "--help", 1, {
                  {"category", "Global"},
                  {"name", "Help"}
               });
//   addCmdRoute("fhzcfullbuild", "fhzc fullbuild --version= [--aliyun]", 1, {
//                  {"category", "Fhzc"},
//                  {"name", "Build"},
//                  {"action", "fullbuild"}
//               });
//   addCmdRoute("fhzcdiffbuild", "fhzc diffbuild --from= --to= [--aliyun]", 1, {
//                  {"category", "Fhzc"},
//                  {"name", "Build"},
//                  {"action", "diffbuild"}
//               });
//   addCmdRoute("fhshopfullbuild", "fhshop fullbuild --version= [--aliyun]", 1, {
//                  {"category", "Fhshop"},
//                  {"name", "Build"},
//                  {"action", "fullbuild"}
//               });
//   addCmdRoute("fhshopdiffbuild", "fhshop diffbuild --from= --to= [--aliyun]", 1, {
//                  {"category", "Fhshop"},
//                  {"name", "Build"},
//                  {"action", "diffbuild"}
//               });
   addCmdRoute("rmmgrrpmbuild", "rmmgr rpmbuild [--projectDir=] [--buildDir=] --version=", 1, {
                  {"category", "RmMgr"},
                  {"name", "Build"},
                  {"action", "rpmbuild"}
               });
   addCmdRoute("upgrademgrmasterrpmbuild", "upgrademgrmaster rpmbuild [--projectDir=] [--buildDir=] --version=", 1, {
                  {"category", "Upgrademgr"},
                  {"name", "Build"},
                  {"subsystem", "master"},
                  {"action", "rpmbuild"}
               });
   addCmdRoute("upgrademgrslaverpmbuild", "upgrademgrslave rpmbuild [--projectDir=] [--buildDir=] --version=", 1, {
                  {"category", "Upgrademgr"},
                  {"name", "Build"},
                  {"subsystem", "slave"},
                  {"action", "rpmbuild"}
               });
   addCmdRoute("cloudcontrollerrpmbuild", "cloudcontroller rpmbuild [--projectDir=] [--buildDir=] --version=", 1, {
                  {"category", "CloudController"},
                  {"name", "Build"},
                  {"action", "rpmbuild"}
               });
   addCmdRoute("cloudcontrollerwebfullbuild", "cloudcontroller webfullbuild --version= [--aliyun]", 1, {
                  {"category", "CloudController"},
                  {"name", "Build"},
                  {"action", "webfullbuild"}
               });
   addCmdRoute("cloudcontrollerwebdiffbuild", "cloudcontroller webdiffbuild --from= --to= [--aliyun]", 1, {
                  {"category", "CloudController"},
                  {"name", "Build"},
                  {"action", "webdiffbuild"}
               });
   addCmdRoute("deploysystemmetaserverbuild", "deploysystem metaserver rpmbuild [--projectDir=] [--buildDir=] --version=", 1, {
                  {"category", "DeploySystem"},
                  {"name", "Build"},
                  {"action", "metaserver"}
               });
   addCmdRoute("deploysystemluoxibuild", "deploysystem luoxi rpmbuild [--projectDir=] [--buildDir=] --version=", 1, {
                  {"category", "DeploySystem"},
                  {"name", "Build"},
                  {"action", "luoxi"}
               });
   addCmdRoute("zhuchaowebfullbuild", "zhuchao webfullbuild --version= [--aliyun]", 1, {
                  {"category", "ZhuChao"},
                  {"name", "Build"},
                  {"action", "webfullbuild"}
               });
   addCmdRoute("zhuchaowebdiffbuild", "zhuchao webdiffbuild --from= --to= [--aliyun]", 1, {
                  {"category", "ZhuChao"},
                  {"name", "Build"},
                  {"action", "webdiffbuild"}
               });
}

}//releasemgr