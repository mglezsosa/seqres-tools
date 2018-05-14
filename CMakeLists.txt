cmake_minimum_required(VERSION 3.9)
project(hiclures-tools)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fopenmp")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hiclures main.c sequence.c sequence.h filehandle.h filehandle.c)
target_link_libraries(hiclures m)
