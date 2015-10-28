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
//           "command_runner.h",
//           "option_pool.cpp",
//           "option_pool.h",
       ]
   }
   Group {
      name : "command"
      prefix : name + '/'
      files : [
//         "command_fhzc.h",
//         "command_fhzc.cpp"
      ]
   }
}
