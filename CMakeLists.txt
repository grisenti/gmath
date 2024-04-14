cmake_minimum_required(VERSION 3.15.0)

project(gmath LANGUAGES CXX)

include(cmake/warnings.cmake)

add_library(gmath STATIC)
target_include_directories(gmath PUBLIC include)
target_compile_features(gmath PUBLIC cxx_std_23)
target_sources(gmath PRIVATE
        include/gmath/geometry/line.hpp
        include/gmath/geometry/normal3.hpp
        include/gmath/geometry/plane.hpp
        include/gmath/geometry/point.hpp
        include/gmath/matrix/mat2.hpp
        include/gmath/matrix/mat3.hpp
        include/gmath/matrix/mat4.hpp
        include/gmath/matrix/matrix.hpp
        include/gmath/matrix/matrix_base.hpp
        include/gmath/transform/transform2D.hpp
        include/gmath/transform/transform3D.hpp
        include/gmath/vector/geometric_vector.hpp
        include/gmath/vector/octahedral_vector.hpp
        include/gmath/vector/unit_vector.hpp
        include/gmath/vector/vec2.hpp
        include/gmath/vector/vec3.hpp
        include/gmath/vector/vec4.hpp
        include/gmath/vector/vec_base.hpp
        include/gmath/vector/vecn.hpp
        include/gmath/array.hpp
        include/gmath/array_algorithms.hpp
        include/gmath/base.hpp
        include/gmath/constants.hpp
        include/gmath/debug.hpp
        include/gmath/formatting.hpp
        include/gmath/geometry.hpp
        include/gmath/mat.hpp
        include/gmath/numeric_utils.hpp
        include/gmath/quaternion.hpp
        include/gmath/units.hpp
        include/gmath/vec.hpp

        src/geometry/line.cpp
        src/geometry/plane.cpp
        src/matrix/mat2.cpp
        src/matrix/mat3.cpp
        src/matrix/mat4.cpp
        src/transform/transform2D.cpp
        src/transform/transform3D.cpp
        src/vector/octahedral_vector.cpp
)
enable_warnings(gmath WARNINGS_AS_ERRORS_ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DGMATH_DEBUG")

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()