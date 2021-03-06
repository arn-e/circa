
solution "Circa"
    configurations { "Debug", "Release" }
    language "C++"
    includedirs {"include"}
    flags { "Symbols" }
    targetdir "build"
    objdir "build/obj"

    configuration "Release"
        flags { "OptimizeSpeed" }

    configuration "Debug"
        defines { "DEBUG" }

    project "static_lib"
        kind "StaticLib"
        targetname "circa"
        location "src"
        files {
            "src/*.cpp",
            "src/generated/all_builtin_functions.cpp",
            "src/generated/all_builtin_types.cpp",
            "src/generated/setup_builtin_functions.cpp",
            "src/generated/stdlib_script_text.cpp",
            }
        includedirs {"src"}

        configuration "Debug"
            targetname "circa_d"

    project "command_line"
        kind "ConsoleApp"
        targetname "circa"
        location "src"
        defines { "CIRCA_USE_LINENOISE" }
        files {
            "src/command_line/build_tool.cpp",
            "src/command_line/command_line.cpp",
            "src/command_line/command_line_main.cpp",
            "src/command_line/debugger_repl.cpp",
            "src/command_line/exporting_parser.cpp",
            "src/command_line/file_checker.cpp",
            "src/command_line/generate_cpp.cpp",
            "3rdparty/linenoise/linenoise.c"
        }
        links {"static_lib"}
        includedirs { "src", "3rdparty/linenoise" }

        configuration "Debug"
            targetname "circa_d"

    project "unit_tests"
        kind "ConsoleApp"
        location "src"
        files {"src/unit_tests/*.cpp"}
        includedirs {"src"}
        links {"static_lib"}
