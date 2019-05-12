add_executable(PlaneWorld EXCLUDE_FROM_ALL main.cc)
target_link_libraries(PlaneWorld matrix shape material sphere tuple canvas color
    ray intersection light material world camera plane pattern)
