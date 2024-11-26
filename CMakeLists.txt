cmake_minimum_required(VERSION 3.10)
project(LidarDriver)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
	src/FileReader.cpp
	src/LidarDriver.cpp)
	
add_executable(main
	src/main.cpp)
	
target_link_libraries(main ${PROJECT_NAME})
