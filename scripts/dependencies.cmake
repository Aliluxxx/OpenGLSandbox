# Include dirs
set(SANDBOX_INCLUDE_DIRS
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/sandbox-core/src
)

# Library dirs
set(SANDBOX_LIB_DIRS
	"sandbox-core"
)

# Submodule libraries
list(APPEND SANDBOX_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/sandbox-core/libs/assimp/include
	${CMAKE_SOURCE_DIR}/sandbox-core/libs/assimp/include
	${CMAKE_SOURCE_DIR}/sandbox-core/libs/glad/include
	${CMAKE_SOURCE_DIR}/sandbox-core/libs/glfw/include
	${CMAKE_SOURCE_DIR}/sandbox-core/libs/glm
	${CMAKE_SOURCE_DIR}/sandbox-core/libs/spdlog/include
	${CMAKE_SOURCE_DIR}/sandbox-core/libs/stb/include
)
list(APPEND SANDBOX_LIB_DIRS
	assimp
	glad
	glfw
	stb
)
