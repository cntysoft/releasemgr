import qbs 1.0
ReleaseMgrApplication
{
   name : "releasemgr"
   targetName : "releasemgr"
   cpp.includePaths: base.concat([
                                    "."
                                 ])
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
         "option_pool.h",
         "option_pool.cpp"
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
