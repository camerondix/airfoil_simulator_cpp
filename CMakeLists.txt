cmake_minimum_required(VERSION 3.14)
project(airfoils_cpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(
    src
    src/geometry
    src/linear_Algebra
    src/aerodynamics
)

include(FetchContent)
FetchContent_Declare(
    matplotlibcpp
    URL https://github.com/lava/matplotlib-cpp/archive/refs/heads/master.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(matplotlibcpp)

add_executable(
    airfoil_simulator
    src/aerodynamics/airfoil.cpp
    src/aerodynamics/panel.cpp
    src/aerodynamics/panel_methods.cpp
    src/geometry/line_segment.cpp
    src/geometry/point.cpp
    src/geometry/polygon.cpp
    src/geometry/vector.cpp
    src/linear_algebra/matrix.cpp
    src/main.cpp
)
target_link_libraries(airfoil_simulator matplotlib_cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
    unit_test
    src/aerodynamics/airfoil.cpp
    src/aerodynamics/panel.cpp
    src/aerodynamics/panel_methods.cpp
    src/geometry/line_segment.cpp
    src/geometry/point.cpp
    src/geometry/polygon.cpp
    src/geometry/vector.cpp
    src/linear_algebra/matrix.cpp
    test/unit_test/aerodynamics/airfoil.cpp
    test/unit_test/aerodynamics/panel.cpp
    test/unit_test/aerodynamics/panel_methods.cpp
    test/unit_test/geometry/line_segment.cpp
    test/unit_test/geometry/point.cpp
    test/unit_test/geometry/point_cloud.cpp
    test/unit_test/geometry/polygon.cpp
    test/unit_test/geometry/vector.cpp
    test/unit_test/linear_algebra/matrix.cpp
)
target_link_libraries(unit_test gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_test)