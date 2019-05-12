cmake_minimum_required(VERSION 3.12)

add_library(pattern)
target_sources(pattern PRIVATE pattern.cc)

set(LIBS ${LIBS} pattern CACHE INTERNAL "")
