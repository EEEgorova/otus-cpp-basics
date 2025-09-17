cmake_minimum_required(VERSION 3.7.2)

project(grep)

add_executable(GrepMain GrepMain.cpp)
set_target_properties(GrepMain PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)