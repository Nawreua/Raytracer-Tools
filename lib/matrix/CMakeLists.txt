cmake_minimum_required(VERSION 3.12)

add_library(matrix)
target_sources(matrix PRIVATE "matrix.cc")

set(LIBS ${LIBS} matrix CACHE INTERNAL "")
