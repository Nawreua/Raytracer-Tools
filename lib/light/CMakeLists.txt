cmake_minimum_required(VERSION 3.12)

add_library(light)
target_sources(light PRIVATE "light.cc")

set(LIBS ${LIBS} light CACHE INTERNAL "")
