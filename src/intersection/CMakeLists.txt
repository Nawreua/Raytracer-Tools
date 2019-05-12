cmake_minimum_required(VERSION 3.12)

add_library(intersection)
target_sources(intersection PRIVATE "intersection.cc")

set(LIBS ${LIBS} intersection CACHE INTERNAL "")
