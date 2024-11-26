cmake_minimum_required(VERSION 3.10)
project(LidarDriver)

set(CMAKE_CXX_STANDARD 11)

add_executable(LidarDriver
	src/main.cpp
	src/FileReader.cpp
	src/LidarDriver.cpp
	)
