import qbs 1.0
ReleaseMgrApplication
{
   name : "releasemgr"
   targetName : "releasemgr"
   Depends { name: "Qt"; submodules: ["sql"] }
   cpp.includePaths: base.concat([
                                    ".","../../libs"
                                 ])
   cpp.defines: base.concat([
                               'RMMGR_VERSION="' + project.rmmgrVersion + '"'
                            ])
   
   files : [
      "application.cpp",
      "application.h",
      "command_runner.cpp",
      "command_runner.h",
      "const.cpp",
      "const.h",
      "main.cpp",
      "types.h",
   ]
   
   Group {
      name : "command"
      prefix : name + '/'
      files : [
         "build_command.cpp",
         "build_command.h",
         "command_repo.h",
         "fhshop_build_command.cpp",
         "fhshop_build_command.h",
         "fhzc_build_command.cpp",
         "fhzc_build_command.h",
         "global_command.cpp",
         "global_command.h",
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
      name : "zhuchao_task"
      prefix : "task/zhuchao/"
      files : [
           "web/diff_build_task_mgr.cpp",
           "web/diff_build_task_mgr.h",
           "web/diff_build_tasks.cpp",
           "web/diff_build_tasks.h",
           "web/full_build_task_mgr.cpp",
           "web/full_build_task_mgr.h",
           "web/full_build_tasks.cpp",
           "web/full_build_tasks.h",
       ]
   }
   
   Group {
      name : "fhshop_task"
      prefix:"task/fhshop/"
      files : [
         "diff/clear.cpp",
         "diff/clear.h",
         "diff/generate_diff_metainfo.h",
         "diff/generate_diff_metainfo.cpp",
         "diff/generate_versioninfo.h",
         "diff/generate_versioninfo.cpp",
         "diff/diffbuild_abstract_task.cpp",
         "diff/diffbuild_abstract_task.h",
         "diff/setup_diff_const.cpp",
         "diff/setup_dist_const.h",
         "diff/analysis_database.h",
         "diff/analysis_database.cpp",
         "diff/copy_upgrade_script.h",
         "diff/copy_upgrade_script.cpp",
         "diff/compress.h",
         "diff/compress.cpp",
         "diff/taskmgr.cpp",
         "diff/taskmgr.h",
         "full/taskmgr.cpp",
         "full/taskmgr.h",
         "full/fullbuild_abstract_task.h",
         "full/fullbuild_abstract_task.cpp",
         "full/clear.h",
         "full/clear.cpp",
         "full/copy_project_files.h",
         "full/copy_project_files.cpp",
         "full/build_js_projects.h",
         "full/build_js_projects.cpp",
         "full/dump_mysql.h",
         "full/dump_mysql.cpp",
         "full/generate_versioninfo.h",
         "full/generate_versioninfo.cpp",
         "full/setup_config.h",
         "full/setup_config.cpp",
         "full/setup_dist_const.h",
         "full/setup_dist_const.cpp",
         "full/compress.h",
         "full/compress.cpp",
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
         "diff/compress.cpp",
         "diff/compress.h",
         "diff/copy_upgrade_script.cpp",
         "diff/copy_upgrade_script.h",
         "diff/diffbuild_abstract_task.cpp",
         "diff/diffbuild_abstract_task.h",
         "diff/generate_diff_metainfo.cpp",
         "diff/generate_diff_metainfo.h",
         "diff/generate_versioninfo.cpp",
         "diff/generate_versioninfo.h",
         "diff/setup_dist_const.cpp",
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
      name : "rmmgr_task"
      prefix: "task/rmmgr/"
      files : [
         "rpm_build_task_mgr.cpp",
         "rpm_build_task_mgr.h",
         "rpm_build_tasks.cpp",
         "rpm_build_tasks.h",
      ]
   }
   
   Group {
      name: "upgrademgr_task"
      prefix: "task/upgrademgr/"
      files:[
         "master/rpm_build_task_mgr.cpp",
         "master/rpm_build_task_mgr.h",
         "master/rpm_build_tasks.cpp",
         "master/rpm_build_tasks.h",
         "slave/rpm_build_task_mgr.cpp",
         "slave/rpm_build_task_mgr.h",
         "slave/rpm_build_tasks.cpp",
         "slave/rpm_build_tasks.h",
      ]
   }
   
   Group {
      name: "cloudcontroller_task"
      prefix: "task/cloudcontroller/"
      files:[
         "rpm/build_rpm.cpp",
         "rpm/build_rpm.h",
         "rpm/clear.cpp",
         "rpm/clear.h",
         "rpm/copy_source_files.cpp",
         "rpm/copy_source_files.h",
         "rpm/make_project_structure.cpp",
         "rpm/make_project_structure.h",
         "rpm/rpmbuild_abstract_task.cpp",
         "rpm/rpmbuild_abstract_task.h",
         "rpm/taskmgr.cpp",
         "rpm/taskmgr.h",
         "web/diff_build_task_mgr.cpp",
         "web/diff_build_task_mgr.h",
         "web/diff_build_tasks.cpp",
         "web/diff_build_tasks.h",
         "web/full_build_task_mgr.cpp",
         "web/full_build_task_mgr.h",
         "web/full_build_tasks.cpp",
         "web/full_build_tasks.h",
      ]
   }
   
   Group {
      name: "deploysystem_task"
      prefix: "task/deploysystem/"
      files:[
         "luoxi/rpm_build_task_mgr.cpp",
         "luoxi/rpm_build_task_mgr.h",
         "luoxi/rpm_build_tasks.cpp",
         "luoxi/rpm_build_tasks.h",
         "metaserver/rpm_build_task_mgr.cpp",
         "metaserver/rpm_build_task_mgr.h",
         "metaserver/rpm_build_tasks.cpp",
         "metaserver/rpm_build_tasks.h",
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