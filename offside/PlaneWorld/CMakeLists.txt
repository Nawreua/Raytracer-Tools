cmake_minimum_required(VERSION 3.12)

add_executable(PlaneWorld EXCLUDE_FROM_ALL)
target_sources(PlaneWorld PRIVATE "main.cc")
target_link_libraries(PlaneWorld PRIVATE matrix shape material sphere tuple
  canvas color ray intersection light material world camera plane pattern)
