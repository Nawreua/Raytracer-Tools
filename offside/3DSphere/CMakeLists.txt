cmake_minimum_required(VERSION 3.12)

add_executable(3DSphere EXCLUDE_FROM_ALL)
target_sources(3DSphere PRIVATE "main.cc")
target_link_libraries(3DSphere PRIVATE matrix shape material sphere tuple
  canvas color ray intersection light material world camera)
