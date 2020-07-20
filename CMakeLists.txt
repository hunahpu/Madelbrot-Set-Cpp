cmake_minimum_required(VERSION 3.7)

project(Mandelbrot)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Mandelbrot src/main.cpp src/fractal.cpp)
target_link_libraries(Mandelbrot ${SDL2_LIBRARIES} pthread)
