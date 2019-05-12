cmake_minimum_required(VERSION 3.12)

add_library(shape)
target_sources(shape PRIVATE "shape.cc")

set(LIBS ${LIBS} shape CACHE INTERNAL "")
