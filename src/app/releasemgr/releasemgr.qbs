import qbs 1.0
ReleaseMgrApplication
{
   name : "releasemgr"
   targetName : "releasemgr"
   files : [
      "application.cpp",
      "application.h",
      "main.cpp"
   ]
   Group {
      name : "parser"
      prefix : name + '/'
      files : [
           "command_runner.cpp",
           "command_runner.h",
       ]
   }
   Group {
      name : "command"
      prefix : name + '/'
      files : [
           "command_meta.cpp",
           "command_meta.h",
           "command_type.h",
       ]
   }
}
