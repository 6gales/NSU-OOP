cmake_minimum_required (VERSION 3.1.0)
project (CSVParser)

set(CMAKE_CXX_STANDARD 14)

add_executable(parser main.cpp CSVParser.hpp)
