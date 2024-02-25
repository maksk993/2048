cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME 2048)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} 
	src/main.cpp 
	src/Game/Game2048.cpp
	src/Graphics/Texture.cpp
	src/Graphics/Sprite.cpp
	src/Graphics/ShaderProgram.cpp
	src/Graphics/VBO.cpp
	src/Graphics/VAO.cpp
	src/Graphics/Renderer.cpp
	src/Utilities/FlexibleSizes.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(res/textures)
add_subdirectory(res/shaders)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glad glfw glm)