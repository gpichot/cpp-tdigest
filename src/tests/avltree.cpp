#include "../src/avltree.hpp"
#define BOOST_TEST_MODULE AvlTreeTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(avl_tree_empty) {
    AvlTree* tree = new AvlTree();

    BOOST_CHECK_EQUAL(tree->root(), 0);
    BOOST_CHECK_EQUAL(tree->size(), 0);

    tree->add(5., 3);
    tree->add(8., 1);
    tree->add(9., 2);
    tree->add(4., 2);
    tree->add(7., 2);
    tree->add(6., 2);
    tree->add(2., 2);
    tree->add(1., 6);
    tree->add(3., 6);

    BOOST_CHECK_EQUAL(tree->checkBalance(), true);
    BOOST_CHECK_EQUAL(tree->checkAggregates(), true);
    BOOST_CHECK_EQUAL(tree->checkIntegrity(), true);
}
