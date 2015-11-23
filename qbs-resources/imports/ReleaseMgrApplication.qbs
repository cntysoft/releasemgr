import qbs 1.0
ReleaseMgrProduct
{
   Depends {name:"cpp"}
   type : "application"
   consoleApplication: true
   destinationDirectory: "bin"
   cpp.cxxLanguageVersion: "c++14"
   cpp.defines: base.concat([
                               'RMGR_INSTALL_ROOT="' + qbs.installRoot + '"',
                               'RMGR_SHARE_RES_DIR="' + qbs.installRoot+'/'+project.resourcesInstallDir+ '"'
                            ])
   Group {
      fileTagsFilter: product.type
      qbs.install: true
      qbs.installDir: project.appInstallDir
   }
}
