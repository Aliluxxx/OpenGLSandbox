cmake_minimum_required(VERSION 3.29)

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library("glad" STATIC)

target_sources("glad"
	PRIVATE
	${HEADERS}
	${SOURCES}
)

target_include_directories("glad"
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_configurations_fn("glad")
set_output_dirs_fn("glad" "libs")
