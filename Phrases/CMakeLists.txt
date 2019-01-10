cmake_minimum_required (VERSION 3.1.0)
project (Phrases)

set(CMAKE_CXX_STANDARD 14)
add_executable(phrases phrases.cpp main.cpp)
add_executable(unittest phrases.cpp test.cpp)

