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

set(SRC_DIR ${CMAKE_SOURCE_DIR}/sandbox/resources)

set(DEST_DIRS
	$<TARGET_FILE_DIR:sandbox>/resources
	${CMAKE_BINARY_DIR}/sandbox/resources
)

foreach(DEST ${DEST_DIRS})
	add_custom_command(TARGET sandbox POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${SRC_DIR}
			${DEST}
	)
endforeach()
