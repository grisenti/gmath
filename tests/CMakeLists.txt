include(FetchContent)
include(../cmake/warnings.cmake)
include(../cmake/sanitizers.cmake)

FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.1)
FetchContent_MakeAvailable(catch)

add_executable(tests
        formatting.cpp
        geometry.cpp
        mat.cpp
        transforms.cpp
        units.cpp
        vec.cpp
)
enable_warnings(tests WARNINGS_AS_ERRORS_OFF)
enable_sanitizers(tests ON ON ON OFF OFF)

target_link_libraries(tests PRIVATE gmath Catch2::Catch2WithMain)

