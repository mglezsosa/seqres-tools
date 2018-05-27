cmake_minimum_required(VERSION 3.9)
project(hiclures-tools)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fopenmp")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hiclures src/main.c src/sequence.c src/sequence.h src/filehandle.h src/filehandle.c src/kmer_counter.c src/kmer_counter.h src/seq_distances.c src/seq_distances.h)
target_link_libraries(hiclures m)
