
add_library (tdigest 
    avltree.hpp
    centroid.hpp
    avltreedigest.hpp 
    tdigest.hpp
    boostavltree.hpp
)
set_target_properties(tdigest PROPERTIES LINKER_LANGUAGE CXX)
add_executable (demo main.cpp)
target_link_libraries (demo tdigest)
set(CMAKE_BUILD_TYPE Debug)
list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -O3 ${CMAKE_CXX_FLAGS}")
