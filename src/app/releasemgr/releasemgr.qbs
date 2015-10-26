import qbs 1.0
ReleaseMgrApplication
{
   name : "releasemgr"
   targetName : "releasemgr"
   files : [
        "application.cpp",
        "application.h",
        "command_type.h",
        "main.cpp",
    ]
   Group {
      name : "parser"
      prefix : "parser/"
      files : [
         "command.h"
      ]
   }
}
