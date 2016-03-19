#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVariant>

#include "const.h"
#include "kernel/settings.h"

namespace releasemgr 
{

using sn::corelib::Settings;

static void init_global_cfg(Settings &settings);
static void init_zhuchao_cfg(Settings &settings);
static void init_fhzc_cfg(Settings &settings);
static void init_fhshop_cfg(Settings &settings);
static void init_rmmgr_cfg(Settings &settings);
static void init_upgrademgr_cfg(Settings &settings);
static void init_cloudcontroller_cfg(Settings &settings);
static void init_deploysystem_cfg(Settings &settings);

void init_defualt_cfg(Settings& settings)
{
   init_global_cfg(settings);
   init_zhuchao_cfg(settings);
   init_fhzc_cfg(settings);
   init_fhshop_cfg(settings);
   init_rmmgr_cfg(settings);
   init_upgrademgr_cfg(settings);
   init_cloudcontroller_cfg(settings);
   init_deploysystem_cfg(settings);
   settings.sync();
}

static void init_global_cfg(Settings& settings)
{
   settings.setValue("db.host", "127.0.0.1", CFG_GROUP_GLOBAL);
   settings.setValue("db.username", "root", CFG_GROUP_GLOBAL);
   settings.setValue("db.password", "cntysoft", CFG_GROUP_GLOBAL);
   settings.setValue("db.charset", "utf8", CFG_GROUP_GLOBAL);
}

static void init_zhuchao_cfg(Settings& settings)
{
   //项目相关文件夹
   settings.setValue("projectDir", "/srv/www/zhuchaodevel", CFG_GROUP_ZHUCHAO);
   settings.setValue("buildDir", "/srv/www/zhuchao-build", CFG_GROUP_ZHUCHAO);
   settings.setValue("diffBuildDir", "/srv/www/zhuchao-diff-build", CFG_GROUP_ZHUCHAO);
   settings.setValue("docBuildDir", "/srv/www/zhuchao-apidoc-build", CFG_GROUP_ZHUCHAO);
   settings.setValue("senchaBuildDir", "PlatformJs/build/production", CFG_GROUP_ZHUCHAO);
   //源码文件夹
   QStringList sourceDirs{
      "Apps", "Data/Framework",
      "Config", "JsLibrary",
      "Library",
      "Modules", "Statics",
      "PlatformJs" , "SysApiHandler",
      "TagLibrary", "index.php"
   };
   settings.setValue("sourceDirs", sourceDirs, CFG_GROUP_ZHUCHAO);
   //源码文件夹
   QStringList docSourceDirsPhp{
      "Library/Cntysoft",
      "Library/ZhuChao",
      "Modules",
      "Apps",
      "SysApiHandler",
      "index.php"
   };
   QStringList docSourceDirsJs{
      //         "PlatformJs/ext/src",
      //         "PlatformJs/ext/packages/sencha-core/src",
      "PlatformJs/ext/packages/ext-ux/src",
      "PlatformJs/ZhuChao/src",
      "PlatformJs/ZhuChao/app.js",
      "PlatformJs/packages/sencha-ext/src",
      "PlatformJs/packages/cntysoft-core/src",
      "PlatformJs/packages/cntysoft-comp/src",
      "PlatformJs/packages/cntysoft-webos/src"
   };
   settings.setValue("docSourceDirs/php", docSourceDirsPhp, CFG_GROUP_ZHUCHAO);
   settings.setValue("docSourceDirs/js", docSourceDirsJs, CFG_GROUP_ZHUCHAO);
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
   settings.setValue("submodules/php", submodulesPhp, CFG_GROUP_ZHUCHAO);
   settings.setValue("submodules/sencha", submodulesSencha, CFG_GROUP_ZHUCHAO);
   settings.setValue("submodules/js", submodulesJs, CFG_GROUP_ZHUCHAO);
   //设置sencha项目相关的
   QStringList senchaProjectsZhuChao{
      "PlatformJs/ZhuChao/resources",
      "PlatformJs/ZhuChao/sass",
      "PlatformJs/ZhuChao/src",
      "PlatformJs/ZhuChao/app.js",
      "PlatformJs/ZhuChao/app.json",
      "PlatformJs/ZhuChao/bootstrap.css",
      "PlatformJs/ZhuChao/bootstrap.js",
      "PlatformJs/ZhuChao/index.html"
   };
   settings.setValue("senchaProjects/ZhuChao", senchaProjectsZhuChao, CFG_GROUP_ZHUCHAO);
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
   settings.setValue("buildDir", "/tmp/releasemgr-build", CFG_GROUP_RMMGR);
}

void init_upgrademgr_cfg(Settings &settings)
{
   settings.setValue("projectDir", "/cntysoft/company/projects/cplusplus/upgrademgr_master", CFG_GROUP_UPGRADEMGR_MASTER);
   settings.setValue("buildDir", "/tmp/upgrademgr_master-build", CFG_GROUP_UPGRADEMGR_MASTER);
   settings.setValue("projectDir", "/cntysoft/company/projects/cplusplus/upgrademgr_slave", CFG_GROUP_UPGRADEMGR_SLAVE);
   settings.setValue("buildDir", "/tmp/upgrademgr_slave-build", CFG_GROUP_UPGRADEMGR_SLAVE);
}

void init_cloudcontroller_cfg(Settings &settings)
{
   settings.setValue("projectDir", "/cntysoft/company/projects/cplusplus/cloud_controller", CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("buildDir", "/tmp/cloudcontroller-build", CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("webProjectDir", "/srv/www/cloudcontrollerdevel", CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("webBuildDir", "/tmp/cloudcontrollerweb-build", CFG_GROUP_CLOUDCONTROLLER);
   
   settings.setValue("docBuildDir", "/tmp/cloudcontroller-apidoc-build", CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("senchaBuildDir", "PlatformJs/build/production", CFG_GROUP_CLOUDCONTROLLER);
   //源码文件夹
   QStringList sourceDirs{
      "Apps", "Data/Framework",
      "Config", "JsLibrary",
      "Library",
      "Modules", "Statics",
      "PlatformJs" , "SysApiHandler",
      "TagLibrary", "index.php"
   };
   settings.setValue("sourceDirs", sourceDirs, CFG_GROUP_CLOUDCONTROLLER);
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
      "PlatformJs/CloudController/src",
      "PlatformJs/CloudController/app.js",
      "PlatformJs/packages/sencha-ext/src",
      "PlatformJs/packages/cntysoft-core/src",
      "PlatformJs/packages/cntysoft-comp/src",
      "PlatformJs/packages/cntysoft-webos/src"
   };
   settings.setValue("docSourceDirs/php", docSourceDirsPhp, CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("docSourceDirs/js", docSourceDirsJs, CFG_GROUP_CLOUDCONTROLLER);
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
   settings.setValue("submodules/php", submodulesPhp, CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("submodules/sencha", submodulesSencha, CFG_GROUP_CLOUDCONTROLLER);
   settings.setValue("submodules/js", submodulesJs, CFG_GROUP_CLOUDCONTROLLER);
   //设置sencha项目相关的
   QStringList senchaProjectsCloudController{
      "PlatformJs/CloudController/resources",
      "PlatformJs/CloudController/sass",
      "PlatformJs/CloudController/src",
      "PlatformJs/CloudController/app.js",
      "PlatformJs/CloudController/app.json",
      "PlatformJs/CloudController/bootstrap.css",
      "PlatformJs/CloudController/bootstrap.js",
      "PlatformJs/CloudController/index.html"
   };
   settings.setValue("senchaProjects/CloudController", senchaProjectsCloudController, CFG_GROUP_CLOUDCONTROLLER);
}

void init_deploysystem_cfg(Settings &settings)
{
   settings.setValue("projectDir", "/cntysoft/company/projects/cplusplus/meta_server", CFG_GROUP_METASERVER);
   settings.setValue("buildDir", "/tmp/metaserver-build", CFG_GROUP_METASERVER);
   settings.setValue("projectDir", "/cntysoft/company/projects/cplusplus/luoxi", CFG_GROUP_LUOXI);
   settings.setValue("buildDir", "/tmp/luoxi-build", CFG_GROUP_LUOXI);
}

}//releasemgr
