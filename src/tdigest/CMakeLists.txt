
add_library (tdigest 
    avltree.cpp
    tdigest.cpp
)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fprofile-arcs -ftest-coverage -DNDEBUG ${CMAKE_CXX_FLAGS}")
list(APPEND CMAKE_C_FLAGS " -O0 -g -fprofile-arcs -ftest-coverage -DNDEBUG ${CMAKE_C_FLAGS}")
list(APPEND CMAKE_EXE_LINKER_FLAGS " -O0 -g -fprofile-arcs -ftest-coverage -DNDEBUG ${CMAKE_EXE_LINKER_FLAGS}")

add_executable (demo main.cpp)
target_link_libraries (demo tdigest)
set(CMAKE_BUILD_TYPE Debug)
