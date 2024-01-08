set_languages("c++23")

add_requires("catch2")

set_policy("build.sanitizer.address", true)
set_policy("build.sanitizer.undefined", true)

target("gmath")
    set_warnings("all", "error")
    set_kind("static")
    add_includedirs("include", {public = true})
    add_files("src/**.cpp")

target("tests")
    set_kind("binary")
    add_files("tests/*.cpp")
    add_deps("gmath")
    add_packages("catch2")
