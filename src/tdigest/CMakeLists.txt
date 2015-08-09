
add_library (tdigest 
    avltree.cpp
    tdigest.cpp
)

add_executable (demo main.cpp)
target_link_libraries (demo tdigest)
set(CMAKE_BUILD_TYPE Debug)
