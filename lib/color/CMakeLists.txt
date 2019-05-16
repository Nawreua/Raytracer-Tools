cmake_minimum_required(VERSION 3.12)

add_library(color)
target_sources(color PRIVATE "color.cc")

set(LIBS ${LIBS} color CACHE INTERNAL "")
