cmake_minimum_required(VERSION 3.0)
project(fastlz)

file(GLOB SOURCES *.cpp *.c)
file(GLOB HEADERS *.hpp *.h)

add_library(fastlz STATIC 
	${SOURCES} ${HEADERS})
