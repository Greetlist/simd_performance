add_rules("mode.debug", "mode.release")

add_requires("pybind11")

target("simd_performance")
    set_kind("binary")
    add_files("src/*.cc")
    set_languages("c++17")
    add_cxflags("-msse", {force=true})
    add_cxflags("-mavx", {force=true})
    add_cxflags("-mavx2", {force=true})
    add_packages("pybind11")

target("calculator")
    set_kind("shared")
    add_includedirs("src")
    add_files("src/pybind/*.cc")
    set_languages("c++17")
    add_packages("pybind11")
