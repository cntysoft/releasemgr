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
         "abstract_command.h"
      ]
   }
   Group {
      name : "kernel"
      prefix : name + '/'
      files : [
           "code_location.cpp",
           "code_location.h",
           "errortype.cpp",
           "erroritem.cpp",
           "erroritem.h",
           "errortype.h",
       ]
   }

   Group {
      name : "global"
      prefix : name + '/'
      files : [
         "global.h",
         "global.cpp"
      ]
   }
   
   Group {
      name : "internal"
      prefix : name + '/'
      files : [
           "assert.cpp",
           "assert.h",
       ]
   }
}
