add_executable(3DSphere EXCLUDE_FROM_ALL main.cc)
target_link_libraries(3DSphere matrix sphere tuple canvas color ray
    intersection light material world camera)
