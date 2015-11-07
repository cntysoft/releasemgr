import qbs 1.0
ReleaseMgrProduct
{
   Depends {name:"releasemgr_core"}
   Depends {name:"cpp"}
   type : "application"
   consoleApplication: true
   destinationDirectory: "bin"
   cpp.cxxLanguageVersion: "c++14"
   Group {
      fileTagsFilter: product.type
      qbs.install: true
      qbs.installDir: project.appInstallDir
   }
}
