cmake_minimum_required(VERSION 3.0)
project(miniguide)

add_executable(miniguide WIN32
	main.cpp)

target_link_libraries(miniguide
	fastlz
	minigui)
