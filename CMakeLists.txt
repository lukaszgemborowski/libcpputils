cmake_minimum_required (VERSION 3.2)
project (libcpputils)

set(CMAKE_CXX_STANDARD 14)
set(project-root ${PROJECT_SOURCE_DIR})
include_directories(include)

add_library(
	utils
	src/filesystem.cc
)

target_link_libraries(
	utils
	stdc++fs
)

add_subdirectory(external/googletest)
add_subdirectory(tests)
