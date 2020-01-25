cmake_minimum_required(VERSION 3.15)
project(Pattern_Recognition)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fopenmp")

add_executable(Pattern_Recognition main.cpp Sequence.h PatternRecognition.h Utils.h)