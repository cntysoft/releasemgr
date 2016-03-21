import qbs 1.0
ReleaseMgrProduct
{
   Depends {name:"cpp"}
   Depends { name: "corelib"}
   type : "application"
   consoleApplication: true
   destinationDirectory: "bin"
   cpp.cxxLanguageVersion: "c++14"
   cpp.defines: base.concat([
                               'RMGR_INSTALL_ROOT="' + project.installRoot + '"',
                               'RMGR_SHARE_RES_DIR="' + project.installRoot+'/'+project.resourcesInstallDir+ '"'
                            ])
   Group {
      fileTagsFilter: product.type
      qbs.install: true
      qbs.installDir: project.appInstallDir
   }
}
