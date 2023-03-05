project(maple_test)

add_executable(
    maple_test
    main.cpp

)
target_include_directories(
    maple_test
    PUBLIC
    ../include
)
target_link_libraries(
    maple_test
    PUBLIC
    maple
)