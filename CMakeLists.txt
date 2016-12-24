cmake_minimum_required(VERSION 3.6)
project(pbrt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main/pbrt.cpp src/core/scene.cpp src/core/scene.h src/core/geometry.cpp src/core/geometry.h src/core/pbrt.h src/core/transform.cpp src/core/transform.h src/core/interaction.cpp src/core/interaction.h src/core/shape.cpp src/core/shape.h src/shapes/sphere.cpp src/shapes/sphere.h)
add_executable(pbrt ${SOURCE_FILES})