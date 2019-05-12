cmake_minimum_required(VERSION 3.12)

add_library(plane)
target_sources(plane PRIVATE "plane.cc")

set(LIBS ${LIBS} plane CACHE INTERNAL "")
