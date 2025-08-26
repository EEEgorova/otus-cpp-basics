cmake_minimum_required(VERSION 3.7.2)

project(09.homework)

add_executable(topk_words topk_words.cpp)
set_target_properties(topk_words PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)