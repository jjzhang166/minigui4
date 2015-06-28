cmake_minimum_required(VERSION 3.0)
project(minigui)

add_library(minigui STATIC
	application.cpp
	resource.cpp
	window.cpp)
