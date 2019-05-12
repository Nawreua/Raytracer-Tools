cmake_minimum_required(VERSION 3.12)

add_executable(cannon EXCLUDE_FROM_ALL)
target_sources(cannon PRIVATE "main.cc")
target_link_libraries(cannon PRIVATE tuple canvas color)
