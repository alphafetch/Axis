cmake_minimum_required(VERSION 3.14)
project(Axis LANGUAGES CXX)

# Header-only lib
add_library(axis INTERFACE)
target_include_directories(axis INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(axis INTERFACE cxx_std_17)

# Only build tests when Axis is the top-level project, so people who pull Axis don't also download GoogleTest
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    option(AXIS_BUILD_TESTS "Build the Axis tests" ON)
else ()
    option(AXIS_BUILD_TESTS "Build the Axis tests" OFF)
endif ()

if (AXIS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()