cmake_minimum_required(VERSION 3.0)
project(minigui)

file(GLOB SOURCES *.cpp *.c)
file(GLOB HEADERS *.hpp *.h)

add_library(minigui STATIC
	${SOURCES} ${HEADERS})

target_link_libraries(minigui 
	gdiplus 
	comctl32)
