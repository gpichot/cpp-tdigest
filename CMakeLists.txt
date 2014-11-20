cmake_minimum_required (VERSION 2.8)
project (ctdigest)
add_subdirectory (src) 
add_subdirectory (tests)
enable_testing ()

add_test (NAME AvlTreeTest COMMAND AvlTreeTest)


list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -DNDEBUG ${CMAKE_CXX_FLAGS}")
