#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVariant>

#include "settings.h"
#include "const.h"

namespace releasemgr 
{

static void init_global_cfg(Settings &settings);
static void init_fhzc_cfg(Settings &settings);
static void init_fhshop_cfg(Settings& settings);
static void init_rmmgr_cfg(Settings& settings);

void init_defualt_cfg(Settings& settings)
{
   init_global_cfg(settings);
   init_fhzc_cfg(settings);
   init_fhshop_cfg(settings);
   init_rmmgr_cfg(settings);
   settings.sync();
}

static void init_global_cfg(Settings& settings)
{
   settings.setValue("db.host", "127.0.0.1", CFG_GROUP_GLOABL);
   settings.setValue("db.username", "root", CFG_GROUP_GLOABL);
   settings.setValue("db.password", "cntysoft", CFG_GROUP_GLOABL);
   settings.setValue("db.charset", "utf8", CFG_GROUP_GLOABL);
}

static void init_fhshop_cfg(Settings& settings)
{
   //项目相关文件夹
   settings.setValue("projectDir", "/srv/www/fenghuangshopdevel", CFG_GROUP_FHSHOP);
   settings.setValue("buildDir", "/srv/www/fhshop-build", CFG_GROUP_FHSHOP);
   settings.setValue("diffBuildDir", "/srv/www/fhshop-diff-build", CFG_GROUP_FHSHOP);
   settings.setValue("docBuildDir", "/srv/www/fhshop-apidoc-build", CFG_GROUP_FHSHOP);
   settings.setValue("senchaBuildDir", "PlatformJs/build/production", CFG_GROUP_FHSHOP);
   //源码文件夹
   QStringList sourceDirs{
      "Apps",
      "Data/Framework",
      "Config",
      "JsLibrary",
      "Library",
      "Modules",
      "Statics",
      "PlatformJs",
      "SysApiHandler",
      "TagLibrary",
      "index.php"
   };
   settings.setValue("sourceDirs", sourceDirs, CFG_GROUP_FHSHOP);
     
   //设置sencha项目相关的
   QStringList senchaProjectsFengHuang{
      "PlatformJs/FengHuang/resources",
      "PlatformJs/FengHuang/sass",
      "PlatformJs/FengHuang/src",
      "PlatformJs/FengHuang/app.js",
      "PlatformJs/FengHuang/app.json",
      "PlatformJs/FengHuang/bootstrap.css",
      "PlatformJs/FengHuang/bootstrap.js",
      "PlatformJs/FengHuang/index.html"
   };
   settings.setValue("senchaProjects/FengHuang", senchaProjectsFengHuang, CFG_GROUP_FHSHOP);
   
   //submodules 相关设置
   QStringList submodulesPhp{
      "Library/Cntysoft",
      "Library/Zend",
      "Library/Vender/VsImage"
   };
   QStringList submodulesSencha{
      "PlatformJs/packages/cntysoft-comp",
      "PlatformJs/packages/cntysoft-core",
      "PlatformJs/packages/cntysoft-webos",
      "PlatformJs/packages/sencha-ext"
   };
   QStringList submodulesJs{
      "JsLibrary/CkEditor",
      "JsLibrary/CodeMirror",
      "JsLibrary/Jquery",
      "JsLibrary/JsSha",
      "JsLibrary/WebUploader"
   };
   settings.setValue("submodules/php", submodulesPhp, CFG_GROUP_FHSHOP);
   settings.setValue("submodules/sencha", submodulesSencha, CFG_GROUP_FHSHOP);
   settings.setValue("submodules/js", submodulesJs, CFG_GROUP_FHSHOP);
   
}

static void init_fhzc_cfg(Settings& settings)
{
   //项目相关文件夹
   settings.setValue("projectDir", "/srv/www/fenghuangdevel", CFG_GROUP_FHZC);
   settings.setValue("buildDir", "/srv/www/fenghuangdevel-build", CFG_GROUP_FHZC);
   settings.setValue("docBuildDir", "/srv/www/fenghuang-apidoc-build", CFG_GROUP_FHZC);
   settings.setValue("senchaBuildDir", "PlatformJs/build/production", CFG_GROUP_FHZC);
   //源码文件夹
   QStringList sourceDirs{
      "Apps", "Data/Framework",
      "Config", "JsLibrary",
      "Library",
      "Modules", "Statics",
      "PlatformJs" , "SysApiHandler",
      "TagLibrary", "index.php"
   };
   settings.setValue("sourceDirs", sourceDirs, CFG_GROUP_FHZC);
   //源码文件夹
   QStringList docSourceDirsPhp{
      "Library/Cntysoft",
      "Library/FengHuang",
      "Modules",
      "Apps",
      "SysApiHandler",
      "index.php"
   };
   QStringList docSourceDirsJs{
      //         "PlatformJs/ext/src",
      //         "PlatformJs/ext/packages/sencha-core/src",
      "PlatformJs/ext/packages/ext-ux/src",
      "PlatformJs/FengHuang/src",
      "PlatformJs/FengHuang/app.js",
      "PlatformJs/packages/sencha-ext/src",
      "PlatformJs/packages/cntysoft-core/src",
      "PlatformJs/packages/cntysoft-comp/src",
      "PlatformJs/packages/cntysoft-webos/src"
   };
   settings.setValue("docSourceDirs/php", docSourceDirsPhp, CFG_GROUP_FHZC);
   settings.setValue("docSourceDirs/js", docSourceDirsJs, CFG_GROUP_FHZC);
   //submodules 相关设置
   QStringList submodulesPhp{
      "Library/Cntysoft",
      "Library/Zend",
      "Library/Vender/VsImage"
   };
   QStringList submodulesSencha{
      "PlatformJs/packages/cntysoft-comp",
      "PlatformJs/packages/cntysoft-core",
      "PlatformJs/packages/cntysoft-webos",
      "PlatformJs/packages/sencha-ext"
   };
   QStringList submodulesJs{
      "JsLibrary/CkEditor",
      "JsLibrary/CodeMirror",
      "JsLibrary/Jquery",
      "JsLibrary/JsSha",
      "JsLibrary/WebUploader"
   };
   settings.setValue("submodules/php", submodulesPhp, CFG_GROUP_FHZC);
   settings.setValue("submodules/sencha", submodulesSencha, CFG_GROUP_FHZC);
   settings.setValue("submodules/js", submodulesJs, CFG_GROUP_FHZC);
   //设置sencha项目相关的
   QStringList senchaProjectsFengHuang{
      "PlatformJs/FengHuang/resources",
      "PlatformJs/FengHuang/sass",
      "PlatformJs/FengHuang/src",
      "PlatformJs/FengHuang/app.js",
      "PlatformJs/FengHuang/app.json",
      "PlatformJs/FengHuang/bootstrap.css",
      "PlatformJs/FengHuang/bootstrap.js",
      "PlatformJs/FengHuang/index.html"
   };
   settings.setValue("senchaProjects/FengHuang", senchaProjectsFengHuang, CFG_GROUP_FHZC);
}

void init_rmmgr_cfg(Settings &settings)
{
   settings.setValue("projectDir", "/cntysoft/company/projects/cplusplus/releasemgr", CFG_GROUP_RMMGR);
   settings.setValue("buildDir", "/tmp/relasemgr-build", CFG_GROUP_RMMGR);
}

}//releasemgr
