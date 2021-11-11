cmake_minimum_required(VERSION 3.20)
project(lab_3_main)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_3_main main.cpp)

include_directories(../lib)

target_link_libraries(lab_3_main lab_3_lib)