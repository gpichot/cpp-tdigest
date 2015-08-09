project(cpptdigest-tests)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable (AvlTreeTest avltree.cpp)

target_link_libraries (AvlTreeTest
    tdigest
    ${GTEST_BOTH_LIBRARIES}
)

add_test(TestAvlTree AvlTreeTest)
