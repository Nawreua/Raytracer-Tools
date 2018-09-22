add_executable(shadow_sphere EXCLUDE_FROM_ALL main.cc)
target_link_libraries(shadow_sphere matrix sphere tuple canvas color ray
    intersection)
