cmake_minimum_required(VERSION 3.5)

project(hw6)

add_executable(containers containers.h main.cpp)

set_target_properties(containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

