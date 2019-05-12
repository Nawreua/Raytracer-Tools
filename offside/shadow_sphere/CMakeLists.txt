cmake_minimum_required(VERSION 3.12)

add_executable(shadow_sphere EXCLUDE_FROM_ALL)
target_sources(shadow_sphere PRIVATE "main.cc")
target_link_libraries(shadow_sphere PRIVATE matrix shape material sphere tuple
  canvas color ray intersection)
