cmake_minimum_required(VERSION 3.29)

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library("stb" STATIC)

target_sources("stb"
	PRIVATE
	${HEADERS}
	${SOURCES}
)

target_include_directories("stb"
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_configurations_fn("stb")
set_output_dirs_fn(stb "libs")
