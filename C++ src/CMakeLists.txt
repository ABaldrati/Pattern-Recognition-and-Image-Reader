cmake_minimum_required(VERSION 3.15)
project(Pattern_Recognition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fopenmp")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(Boost  REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Pattern_Recognition mainPR.cpp Matrix.h Utils.h PatternRecognition.h)
add_executable(Image_Reader mainIM.cpp ImageReader.h ImageReader.cpp)
add_executable(Full_Execution mainFull.cpp Matrix.h Utils.h PatternRecognition.h ImageReader.cpp ImageReader.h)

target_link_libraries(Pattern_Recognition ${OpenCV_LIBS})
target_link_libraries(Pattern_Recognition stdc++fs)
target_link_libraries(Pattern_Recognition boost_thread boost_system)

target_link_libraries(Image_Reader ${OpenCV_LIBS})
target_link_libraries(Image_Reader stdc++fs)
target_link_libraries(Image_Reader boost_thread boost_system)

target_link_libraries(Full_Execution ${OpenCV_LIBS})
target_link_libraries(Full_Execution stdc++fs)
target_link_libraries(Full_Execution boost_thread boost_system)