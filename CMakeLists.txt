cmake_minimum_required (VERSION 2.8)

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g -fprofile-arcs -ftest-coverage")
list(APPEND CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage")
list(APPEND CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage")

add_subdirectory (src) 
