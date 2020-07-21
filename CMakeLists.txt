cmake_minimum_required(VERSION 3.7)

project(Mandelbrot)
set (CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

add_executable(Mandelbrot src/main.cpp src/fractal.cpp src/renderer.cpp)
target_link_libraries(Mandelbrot ${SDL2_LIBRARIES} pthread)
