add_rules("mode.debug", "mode.release")
includes("proxygen.lua")

option("include_logging")
    set_showmenu(true)
    set_description("Include verbose logging on run")
    add_defines("VERBOSE")


target("doorstop")
    set_kind("shared")
    set_optimize("smallest")
    add_options("include_logging")

    if is_plat("windows") or is_plat("mingw") then
        add_proxydef("src/windows/proxy/proxylist.txt")
        add_files("src/windows/*.c")

        add_defines("UNICODE")
    end

    add_files("src/*.c")
    add_files("src/config/*.c")
    add_files("src/util/*.c")