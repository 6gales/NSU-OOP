cmake_minimum_required (VERSION 3.1.0)
project (Resolver)

set(CMAKE_CXX_STANDARD 14)

add_executable(resolver main.cpp Resolver.cpp)
add_executable(strResolver mainStr.cpp Resolver.cpp)
add_executable(doubleResolver mainDouble.cpp Resolver.cpp)
add_executable(unittest Resolver.cpp test.cpp)
