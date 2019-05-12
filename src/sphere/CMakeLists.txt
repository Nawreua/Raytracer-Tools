cmake_minimum_required(VERSION 3.12)

add_library(sphere)
target_sources(sphere PRIVATE "sphere.cc")

set(LIBS ${LIBS} sphere CACHE INTERNAL "")
