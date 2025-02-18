add_rules("mode.debug", "mode.release")

target("simd_performance")
    set_kind("binary")
    add_files("src/*.cc")
    set_languages("c++17")
    add_cxflags("-msse", {force=true})
    add_cxflags("-mavx", {force=true})
    add_cxflags("-mavx2", {force=true})
