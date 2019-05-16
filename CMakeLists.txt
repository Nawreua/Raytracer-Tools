# SETUP
cmake_minimum_required(VERSION 3.12)
project("The RayTracer Challenge"
        VERSION 0.9
        DESCRIPTION "A collection of raytracing tools"
        LANGUAGES CXX)

# BUILD OPTIONS
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Not build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address --coverage")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# LIBRARIES
add_subdirectory(lib)
add_subdirectory(offside)

# TESTS
find_package(GTest)
if(GTest_FOUND)
  add_executable(check EXCLUDE_FROM_ALL)
  target_sources(check PRIVATE
    "tests/tests_camera.cc"
    "tests/tests_canvas.cc"
    "tests/tests.cc"
    "tests/tests_color.cc"
    "tests/tests_intersection.cc"
    "tests/tests_light.cc"
    "tests/tests_material.cc"
    "tests/tests_matrix.cc"
    "tests/tests_matrix_transformations.cc"
    "tests/tests_pattern.cc"
    "tests/tests_plane.cc"
    "tests/tests_ray.cc"
    "tests/tests_shape.cc"
    "tests/tests_sphere.cc"
    "tests/tests_tuple.cc"
    "tests/tests_world.cc"
    "tests/tests.cc")
  target_link_libraries(check PRIVATE Raytracer::core GTest::GTest)
  set_target_properties(check
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  gtest_discover_tests(check)
endif()
