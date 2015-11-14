import qbs 1.0
import ReleaseMgrFuncs
ReleaseMgrLibrary
{
   name : "releasemgr_core"
   targetName : "releasemgrcore"
   cpp.dynamicLibraries: base
   cpp.includePaths: base.concat([
                                    "."
                                 ])
   Group {
      name : "command"
      prefix: name + '/'
      files : [
       ]
   }
   Group {
      name : "kernel"
      prefix : name + '/'
      files : [
         "erroritem.cpp",
         "erroritem.h",
         "errorinfo.h",
         "errorinfo.cpp",
         "code_location.h",
         "code_location.cpp"
      ]
   }
   
   Group {
      name : "global"
      prefix : name + '/'
      files : [
           "common_funcs.cpp",
           "common_funcs.h",
           "const.h",
           "global.h",
           "global.cpp",
       ]
   }
   
   Group {
      name : "internal"
      prefix : name + '/'
      files : [
         //         "assert.cpp",
         //         "assert.h",
      ]
   }
   Group {
      name : "io"
      prefix : name + '/'
      files : [
           "terminal.cpp",
           "terminal.h",
       ]
   }
}
