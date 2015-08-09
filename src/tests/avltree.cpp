#include "../tdigest/avltree.hpp"

#include <gtest/gtest.h>

TEST(AvlTreeTest, GenericTest) {
    AvlTree* tree = new AvlTree();

    ASSERT_EQ(tree->root(), 0);
    ASSERT_EQ(tree->size(), 0);

    tree->add(5., 3);
    tree->add(8., 1);
    tree->add(9., 2);
    tree->add(4., 2);
    tree->add(7., 2);
    tree->add(6., 2);
    tree->add(2., 2);
    tree->add(1., 6);
    tree->add(3., 6);

    ASSERT_EQ(tree->checkBalance(), true);
    ASSERT_EQ(tree->checkAggregates(), true);
    ASSERT_EQ(tree->checkIntegrity(), true);
}
