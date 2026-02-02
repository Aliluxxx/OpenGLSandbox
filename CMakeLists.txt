cmake_minimum_required(VERSION 3.29)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Sandbox VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_PARALLEL_LEVEL 4)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS_DIST "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DIST "" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_DIST "" CACHE STRING "" FORCE)

set(OUTPUT_DIR "$<CONFIG>")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_definitions(-DSB_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_definitions(-DSB_PLATFORM_MACOSX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-DSB_PLATFORM_WINDOWS)
else()
    message(WARNING "OS not recognized!")
endif()

function(set_configurations_fn target)
	target_compile_options(${target} PRIVATE
		# GCC / Clang
		$<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-O0 -g -DDEBUG -DSB_DEBUG>
		$<$<AND:$<CONFIG:Release>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-O2 -g -DSB_RELEASE>
		$<$<AND:$<CONFIG:Dist>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-O3 -DNDEBUG -DSB_DIST>

		# MSVC
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Od /Zi /DDEBUG /DSB_DEBUG>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 /Zi /DSB_RELEASE>
		$<$<AND:$<CONFIG:Dist>,$<CXX_COMPILER_ID:MSVC>>:/O2 /DNDEBUG /DSB_DIST>
	)

	target_link_options(${target} PRIVATE
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/DEBUG>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/DEBUG>
	)
endfunction()

function(set_output_dirs_fn target)
	set(options ${ARGN})
	if(options)
		set(filter "/${options}")
	else()
		set(filter "")
	endif()
	set_target_properties(${target} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/bin/${OUTPUT_DIR}${filter}>"
		LIBRARY_OUTPUT_DIRECTORY "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/bin/${OUTPUT_DIR}${filter}>"
		ARCHIVE_OUTPUT_DIRECTORY "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/bin/${OUTPUT_DIR}${filter}>"
	)
endfunction()

include(scripts/dependencies.cmake)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
add_subdirectory("sandbox-core/libs/glfw")
set_configurations_fn(glfw)
set_output_dirs_fn(glfw "libs")

# GLM
add_subdirectory("sandbox-core/libs/glm")
set_configurations_fn(glm)

# SPDLOG
add_subdirectory("sandbox-core/libs/spdlog")
set_configurations_fn(spdlog)

add_subdirectory("sandbox")
add_subdirectory("sandbox-core")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "sandbox")

# Create the "libs" filter

function(get_all_targets result dir)
	get_property(targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
	set(allTargets ${targets})

	get_property(subdirs DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
	foreach(subdir ${subdirs})
		get_all_targets(subTargets ${subdir})
		list(APPEND allTargets ${subTargets})
	endforeach()

	set(${result} ${allTargets} PARENT_SCOPE)
endfunction()

get_all_targets(allTargets ${CMAKE_CURRENT_SOURCE_DIR})
foreach(t ${allTargets})
	if(t MATCHES "^(sandbox|sandbox-core|ZERO_CHECK)$")
		continue()
	endif()

	get_target_property(targetDir ${t} SOURCE_DIR)
	if(NOT targetDir)
		continue()
	endif()

	file(TO_CMAKE_PATH "${targetDir}" targetDir)

	string(FIND "${targetDir}" "/libs/" libsIndex)
	if(libsIndex EQUAL -1)
		set(folder "libs/other")
	else()
		math(EXPR start "${libsIndex} + 6")
		string(SUBSTRING "${targetDir}" ${start} -1 subPath)

		string(REPLACE "/" ";" parts "${subPath}")
		list(GET parts 0 libName)

		set(folder "libs/${libName}")
	endif()

	set_target_properties(${t} PROPERTIES FOLDER "${folder}")
endforeach()
