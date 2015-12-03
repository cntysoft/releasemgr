import qbs 1.0
ReleaseMgrApplication
{
   name : "releasemgr"
   targetName : "releasemgr"
   Depends {name:"releasemgr_core"}
   Depends { name: "Qt"; submodules: ["sql"] }
   cpp.includePaths: base.concat([
                                    "."
                                 ])
   
   files : [
      "application.cpp",
      "application.h",
      "const.cpp",
      "const.h",
      
      "main.cpp",
      "settings.cpp",
      "settings.h",
      "types.h",
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
         "abstract_command.h",
         "abstract_command.cpp",
         "command_category.h",
         "command_meta.cpp",
         "command_meta.h",
         "command_repo.h",
         "fhzc_build_command.cpp",
         "fhzc_build_command.h",
         "global_help_command.cpp",
         "global_help_command.h",
         "global_version_command.cpp",
         "global_version_command.h",
      ]
   }
   Group {
      name : "task"
      prefix : name + '/'
      files: [
         "abstract_task.cpp",
         "abstract_task.h",
         "abstract_taskmgr.cpp",
         "abstract_taskmgr.h",
      ]
   }
   Group {
      name : "fhzc_task"
      prefix : "task/fhzc/"
      files : [
           "diff/analysis_database.cpp",
           "diff/analysis_database.h",
           "diff/clear.cpp",
           "diff/clear.h",
           "diff/diffbuild_abstract_task.cpp",
           "diff/diffbuild_abstract_task.h",
           "diff/generate_diff_metainfo.cpp",
           "diff/generate_diff_metainfo.h",
           "diff/generate_versioninfo.cpp",
           "diff/generate_versioninfo.h",
           "diff/setup_diff_const.cpp",
           "diff/setup_dist_const.h",
           "diff/taskmgr.cpp",
           "diff/taskmgr.h",
           "full/build_js_projects.cpp",
           "full/build_js_projects.h",
           "full/clear.cpp",
           "full/clear.h",
           "full/compress.cpp",
           "full/compress.h",
           "full/copy_project_files.cpp",
           "full/copy_project_files.h",
           "full/dump_mysql.cpp",
           "full/dump_mysql.h",
           "full/fullbuild_abstract_task.cpp",
           "full/fullbuild_abstract_task.h",
           "full/generate_versioninfo.cpp",
           "full/generate_versioninfo.h",
           "full/setup_config.cpp",
           "full/setup_config.h",
           "full/setup_dist_const.cpp",
           "full/setup_dist_const.h",
           "full/taskmgr.cpp",
           "full/taskmgr.h",
       ]
   }
   Group {
      name : "utils"
      prefix : name + '/'
      files : [
           "funcs.cpp",
           "funcs.h",
           "env_detecter.cpp",
           "default_cfg_initializer.cpp",
           "env_detecter.h",
           "stddir.cpp",
           "stddir.h",
       ]
   }   
}