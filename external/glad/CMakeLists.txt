#external/glad/CMakeLists.txt
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(Glad)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)