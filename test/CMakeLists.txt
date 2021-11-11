cmake_minimum_required(VERSION 3.20)
project(lab_3_tests)

set(CMAKE_CXX_STANDARD 20)

### googletest init ###
include(FetchContent)
FetchContent_Declare(
        googletest

        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
### googletest init end ###

add_executable(lab_3_tests test.cpp)

### links to static libs ###
include_directories(../lib)
target_link_libraries(lab_3_tests gtest_main lab_3_lib)