import qbs 1.0
ReleaseMgrProduct
{
   Depends { name:"cpp"}
   type: "dynamiclibrary"
   destinationDirectory: project.libDirName
   cpp.defines: base.concat(type == "staticlibrary" ? ["RM_STATIC_LIB"] : ["RM_LIBRARY"])
   cpp.visibility: "minimal"
   cpp.cxxLanguageVersion: "c++14"
   Group {
      fileTagsFilter: product.type.concat("dynamiclibrary_symlink")
      qbs.install: true
      qbs.installDir: project.libInstallDir
   }
   Export {
      Depends { name: "cpp" }
      Depends { name: "Qt"; submodules: ["core"] }
      cpp.rpaths: project.libRPaths
      cpp.includePaths: [product.sourceDirectory]
   }
}
