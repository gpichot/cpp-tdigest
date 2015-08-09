project(cpptdigest-tests)

enable_testing()
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fprofile-arcs -ftest-coverage -DNDEBUG ${CMAKE_CXX_FLAGS}")
list(APPEND CMAKE_C_FLAGS " -O0 -g -fprofile-arcs -ftest-coverage -DNDEBUG ${CMAKE_C_FLAGS}")
list(APPEND CMAKE_EXE_LINKER_FLAGS " -O0 -g -fprofile-arcs -ftest-coverage -DNDEBUG ${CMAKE_EXE_LINKER_FLAGS}")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable (AvlTreeTest avltree.cpp)

target_link_libraries (AvlTreeTest
    tdigest
    ${GTEST_BOTH_LIBRARIES}
)

add_test(TestAvlTree AvlTreeTest)
