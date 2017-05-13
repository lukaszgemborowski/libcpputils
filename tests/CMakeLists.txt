cmake_minimum_required (VERSION 3.2)
project (tests)

add_executable(
	tests
	array_reader_tests.cc
	block_size_tests.cc
	filesystem_tests.cc
	static_file_reader_tests.cc
)

target_link_libraries(tests utils gtest_main)
