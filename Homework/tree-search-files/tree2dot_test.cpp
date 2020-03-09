#include "tree2dot.h"
#include <vector>
#include <iostream>

template <typename T>
struct TNode
{
    T data = T();
    std::vector< TNode<T> * > children = {};
};

int main()
{
    TNode<int> * pRoot = new TNode<int>;
    pRoot->data = 10;

    TNode<int> * temp;
    temp = new TNode<int>; temp->data = 5;
    pRoot->children.push_back( temp );

    TNode<int> * temp2;
    temp2 = new TNode<int>; temp2->data = 1;
    temp->children.push_back( temp2 );
    temp2 = new TNode<int>; temp2->data = 7;
    temp->children.push_back( temp2 );

    temp = new TNode<int>; temp->data = 15;
    pRoot->children.push_back( temp );

    temp2 = new TNode<int>; temp2->data = 11;
    temp->children.push_back( temp2 );

    /*
     *              10
     *           /     \
     *          5      15
     *         / \     |
     *         1  7    11
     */
    print_dot( pRoot, 
            std::cout, 
            [](TNode<int> const * p_node)->int { return p_node->data; },
            [](TNode<int> const * p_node)->std::vector<TNode<int>*> { return p_node->children; },
            [](TNode<int> const * p_node)->bool { return p_node->data == 15; }
            );
    // see attached tree2dot_test_output.ps
}
