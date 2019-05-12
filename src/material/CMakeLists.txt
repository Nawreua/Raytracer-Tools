cmake_minimum_required(VERSION 3.12)

add_library(material)
target_sources(material PRIVATE "material.cc")

set(LIBS ${LIBS} material CACHE INTERNAL "")
