#external/glad/CMakeLists.txt
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(Glad)

add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)

#CMakeLists.txt
#add_subdirectory(../../.)
#target_link_libraries(${PROJECT_NAME} PRIVATE glad)


