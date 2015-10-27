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
         "option_pool.cpp",
         "option_pool.h",
      ]
   }
}
