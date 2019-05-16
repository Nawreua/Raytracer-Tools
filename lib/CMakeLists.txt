# SETUP
cmake_minimum_required(VERSION 3.12)

# UNIT LIBRARIES
add_library(camera OBJECT)
target_sources(camera
  PRIVATE "camera/camera.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/camera.hh")
target_link_libraries(camera PUBLIC world)
target_include_directories(camera PUBLIC include)

add_library(canvas OBJECT)
target_sources(canvas
  PRIVATE "canvas/canvas.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/canvas.hh")
target_include_directories(canvas PUBLIC include)

add_library(color OBJECT)
target_sources(color
  PRIVATE "color/color.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/color.hh")
target_include_directories(color PUBLIC include)

add_library(intersection OBJECT)
target_sources(intersection
  PRIVATE "intersection/intersection.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/intersection.hh")
target_include_directories(intersection PUBLIC include)

add_library(light OBJECT)
target_sources(light
  PRIVATE "light/light.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/light.hh")
target_include_directories(light PUBLIC include)

add_library(material OBJECT)
target_sources(material
  PRIVATE "material/material.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/material.hh")
target_include_directories(material PUBLIC include)

add_library(matrix OBJECT)
target_sources(matrix
  PRIVATE "matrix/matrix.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/matrix.hh")
target_include_directories(matrix PUBLIC include)

add_library(pattern OBJECT)
target_sources(pattern
  PRIVATE "pattern/pattern.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/pattern.hh")
target_include_directories(pattern PUBLIC include)

add_library(plane OBJECT)
target_sources(plane
  PRIVATE "plane/plane.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/plane.hh")
target_include_directories(plane PUBLIC include)

add_library(ray OBJECT)
target_sources(ray
  PRIVATE "ray/ray.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/ray.hh")
target_link_libraries(ray PUBLIC matrix)
target_include_directories(ray PUBLIC include)

add_library(shape OBJECT)
target_sources(shape
  PRIVATE "shape/shape.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/shape.hh")
target_include_directories(shape PUBLIC include)

add_library(sphere OBJECT)
target_sources(sphere
  PRIVATE "sphere/sphere.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/sphere.hh")
target_include_directories(sphere PUBLIC include)

add_library(tuple OBJECT)
target_sources(tuple
  PRIVATE "tuple/tuple.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/tuple.hh")
target_include_directories(tuple PUBLIC include)

add_library(world OBJECT)
target_sources(world
  PRIVATE "world/world.cc"
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/world.hh")
target_include_directories(world PUBLIC include)

# CORE LIBRARY
add_library(raytracer_coreLib STATIC)
target_link_libraries(raytracer_coreLib PUBLIC camera canvas color intersection
  light material matrix pattern plane ray shape sphere tuple world)

add_library(Raytracer::core ALIAS raytracer_coreLib)
