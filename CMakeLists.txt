cmake_minimum_required(VERSION 3.9)
project(seqres-tools)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fopenmp")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(seqres src/main.c src/sequence.c src/sequence.h src/filehandle.h src/filehandle.c src/kmer_counter.c src/kmer_counter.h src/seq_distances.c src/seq_distances.h src/globals.h src/rw_occurrences.h src/hits.c src/hits.h src/dynamic_array.c src/dynamic_array.h src/rw_occurrences.h src/rw_occurrences.c)
target_link_libraries(seqres m)
