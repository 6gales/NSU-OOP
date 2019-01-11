cmake_minimum_required (VERSION 3.1.0)
project (BattleshipBot)

set(CMAKE_CXX_STANDARD 14)

add_executable(bsbot main.cpp Bot.cpp Field.cpp FinishIt.cpp Strategy.cpp)
add_executable(unittest test.cpp Bot.cpp Field.cpp FinishIt.cpp Strategy.cpp)

