cmake_minimum_required(VERSION 3.29)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable("sandbox")

target_sources("sandbox"
	PRIVATE
	${HEADERS}
	${SOURCES}
)

target_include_directories("sandbox"
	PRIVATE
	${SANDBOX_INCLUDE_DIRS}
)

target_link_libraries("sandbox"
	PRIVATE
	${SANDBOX_LIB_DIRS}
)

set_configurations_fn("sandbox")
set_output_dirs_fn("sandbox")
