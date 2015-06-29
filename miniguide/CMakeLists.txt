cmake_minimum_required(VERSION 3.0)
project(miniguide)

file(GLOB SOURCES *.cpp *.c)
file(GLOB HEADERS *.hpp *.h)

add_executable(miniguide WIN32
	${SOURCES} ${HEADERS})

target_link_libraries(miniguide
	gdiplus 
	comctl32
	fastlz
	minigui)

