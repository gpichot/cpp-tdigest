cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage")

add_subdirectory (src) 
