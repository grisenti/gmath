set_languages("c++23")

add_requires("catch2")

set_policy("build.sanitizer.address", true)
set_policy("build.sanitizer.undefined", true)

target("tests")
    set_kind("binary")
    add_files("tests/*.cpp")
    add_deps("gmath")
    add_packages("catch2")

target("gmath")
    set_warnings("all", "error")
    set_kind("static")
    add_includedirs("src", {public = true})
    add_files("src/**.cpp")

