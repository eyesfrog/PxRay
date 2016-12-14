cmake_minimum_required(VERSION 3.6)
project(pbrt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main/pbrt.cpp src/core/scene.cpp src/core/scene.h src/core/geometry.cpp src/core/geometry.h src/core/pbrt.h)
add_executable(pbrt ${SOURCE_FILES})