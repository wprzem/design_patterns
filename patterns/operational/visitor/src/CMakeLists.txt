cmake_minimum_required(VERSION 3.10)

add_library(visitor 
	visitor.cpp
	plant.cpp)

target_include_directories(visitor 
	PRIVATE 
	${VISITOR_INC_DIR})

