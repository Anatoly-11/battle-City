#CMakeLists.txt
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

SET(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20) 
#target_compile_features(${PROJECT_NAME} PUBLIC c17) 

set(CMAKE_CXX_STANDARD cxx_std_20)
set(CMAKE_C_STANDARD 17)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)
