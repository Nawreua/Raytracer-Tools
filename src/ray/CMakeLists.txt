cmake_minimum_required(VERSION 3.12)

add_library(ray)
target_sources(ray PRIVATE "ray.cc")
target_link_libraries(ray PUBLIC matrix)

set(LIBS ${LIBS} ray CACHE INTERNAL "")
