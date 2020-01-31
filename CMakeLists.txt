cmake_minimum_required(VERSION 2.8)
project(tdd_study)

set(CMAKE_CXX_STANDARD 11)
include_directories("/usr/local/include")
add_executable(tdd_study SoundexTest.cpp main.cpp Soundex.h)
target_link_libraries(tdd_study gtest gmock pthread)