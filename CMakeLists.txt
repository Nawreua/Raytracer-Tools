cmake_minimum_required (VERSION 2.6)

project ("The RayTracer Challenge")

include_directories(src src/tuple src/colors)
add_subdirectory(src)
add_subdirectory(src_offside)
set(LIBS ${LIBS} tuple)
set(LIBS ${LIBS} color)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(check EXCLUDE_FROM_ALL tests/tests.cc)
target_link_libraries(check ${LIBS} ${GTEST_LIBRARIES} pthread)
