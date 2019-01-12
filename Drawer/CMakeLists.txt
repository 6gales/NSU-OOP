cmake_minimum_required (VERSION 3.1.0)
project (Drawer)

set(CMAKE_CXX_STANDARD 14)

add_executable(drawer main.cpp Shape.cpp Drawer.cpp)
add_executable(unittest test.cpp Shape.cpp Drawer.cpp)
