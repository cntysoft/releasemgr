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
        "main.cpp",
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
            "global_help_command.cpp",
            "global_help_command.h",
            "global_version_command.cpp",
            "global_version_command.h",
        ]
    }
    Group {
        files: [
            "abstract_task.cpp",
            "abstract_task.h",
            "abstract_taskmgr.cpp",
            "abstract_taskmgr.h",
        ]
        name : "task"
        prefix : name + '/'
    }
    Group {
        files : [
            "diff/clear.h",
            "full/clear.h",
        ]
        name : "fhzc_task"
        prefix : "task/fhzc/"
    }
}
