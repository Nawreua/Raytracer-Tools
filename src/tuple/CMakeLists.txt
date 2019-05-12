cmake_minimum_required(VERSION 3.12)

add_library(tuple)
target_sources(tuple PRIVATE "tuple.cc")

set(LIBS ${LIBS} tuple CACHE INTERNAL "")
