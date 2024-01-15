include(../cmake/warnings.cmake)

add_library(gmath STATIC)
target_include_directories(gmath PUBLIC ../include)
target_compile_features(gmath PUBLIC cxx_std_23)
target_sources(gmath PRIVATE
        geometry/line.cpp
        geometry/plane.cpp
        matrix/mat2.cpp
        matrix/mat3.cpp
        matrix/mat4.cpp
        transform/transform2D.cpp
        transform/transform3D.cpp
        vector/octahedral_vector.cpp
)
enable_warnings(gmath WARNINGS_AS_ERRORS_ON)