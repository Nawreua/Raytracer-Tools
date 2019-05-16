cmake_minimum_required(VERSION 3.12)

add_library(world)
target_sources(world PRIVATE "world.cc")

set(LIBS ${LIBS} world CACHE INTERNAL "")
