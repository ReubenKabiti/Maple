
project(simple)
add_executable(simple main.cpp)
target_link_libraries(
	simple
	PUBLIC
	maple_xml
)
target_include_directories(
	simple
	PUBLIC
	../../maple_xml
)
