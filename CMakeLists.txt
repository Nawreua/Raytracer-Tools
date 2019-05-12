# SETUP
cmake_minimum_required(VERSION 3.12)
project("The RayTracer Challenge")

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

# INCLUDE
include_directories(src src/tuple src/colors src/canvas src/matrix src/ray
    src/sphere src/intersection src/light src/material src/world
    src/camera src/shape src/plane src/pattern)

# LIBRARIES
set(LIBS ${LIBS} CACHE INTERNAL "")

add_subdirectory(src)
add_subdirectory(offside)

# TESTS
find_package(GTest)
if(GTest_FOUND)
  add_executable(check EXCLUDE_FROM_ALL)
  target_sources(check PRIVATE "tests/tests.cc")
  target_link_libraries(check PRIVATE ${LIBS} GTest::GTest)
  set_target_properties(check
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  gtest_discover_tests(check)
endif()
