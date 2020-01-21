cmake_minimum_required(VERSION 3.15)
project(Pattern_Recognition)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pattern_Recognition main.cpp Sequence.cpp Sequence.h PatternRecognition.cpp PatternRecognition.h Utils.h)