cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O2")

project ("The RayTracer Challenge")

include_directories(src src/tuple src/colors src/canvas src/matrix)
add_subdirectory(src)
add_subdirectory(src_offside)
set(LIBS ${LIBS} tuple)
set(LIBS ${LIBS} color)
set(LIBS ${LIBS} canvas)
set(LIBS ${LIBS} matrix)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(check EXCLUDE_FROM_ALL tests/tests.cc)
target_link_libraries(check ${LIBS} ${GTEST_LIBRARIES} pthread)
