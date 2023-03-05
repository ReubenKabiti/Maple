add_library(
    maple
    file.cpp
    xmlparser.cpp
)

target_include_directories(
    maple
    PUBLIC
    ../include
)