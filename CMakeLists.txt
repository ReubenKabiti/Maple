cmake_minimum_required(VERSION 3.0)

project(
    maple
    VERSION 1.0
)
add_executable(
    maple
    src/file.cpp
    src/main.cpp
)
target_include_directories(
    maple
    PUBLIC
    include
)

