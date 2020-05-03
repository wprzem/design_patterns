cmake_minimum_required(VERSION 3.10)

include(GoogleTest)
add_executable(visitor_test visitor_test.cpp)
target_link_libraries(visitor_test
	PRIVATE
	gtest_main
	visitor)
gtest_discover_tests(visitor_test)
target_include_directories(visitor_test PRIVATE ${VISITOR_INC_DIR})
