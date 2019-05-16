cmake_minimum_required(VERSION 3.12)

add_library(camera)
target_sources(camera PRIVATE "camera.cc")
target_link_libraries(camera PUBLIC world)

set(LIBS ${LIBS} camera CACHE INTERNAL "")
