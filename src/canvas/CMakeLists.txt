cmake_minimum_required(VERSION 3.12)

add_library(canvas)
target_sources(canvas PRIVATE "canvas.cc")

set(LIBS ${LIBS} canvas CACHE INTERNAL "")
