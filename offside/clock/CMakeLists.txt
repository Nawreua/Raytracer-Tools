cmake_minimum_required(VERSION 3.12)

add_executable(clock EXCLUDE_FROM_ALL)
target_sources(clock PRIVATE "main.cc")
target_link_libraries(clock PRIVATE tuple canvas color matrix)
