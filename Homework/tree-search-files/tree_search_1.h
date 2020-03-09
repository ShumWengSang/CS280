#ifndef TREE_SEARCH_1_H
#define TREE_SEARCH_1_H
#include <iostream>
#include <vector>
#include <deque>
#include <stack>

template <typename T>
struct TNode
{
    T data = T();
    std::vector< TNode<T> * > children = {};
};

// recursive implementation of DFS
template <typename T>
TNode<T> const *        // returns first found node that is equal to val
tree_depth_first_search_rec( TNode<T> const * pRoot, T const & val )
{
    if(!pRoot)
        return nullptr;
    if(pRoot->data == val)
        return pRoot;
    for(auto* node : pRoot->children)
    {
        auto* isNode = tree_depth_first_search_rec(node, val);
        if(isNode)
            return isNode;
    }
    return nullptr;
}

// iterative implementation of DFS
// use stack (push,top,pop) or vector(push_back,back,pop_back)
// when inserting children, make sure they will be dicovered in the same
// order as in TNode's array children
template <typename T>
TNode<T> const *        // returns first found node that is equal to val
tree_depth_first_search_iter( TNode<T> const * pRoot, T const & val )
{
    std::stack<TNode<T>*> openlist;
    openlist.push(const_cast<TNode<T>*>(pRoot));

    while ( openlist.size() > 0 ) {
        TNode<T>* node = openlist.top();
        openlist.pop();

        // insert children in the order ( 0,1,2,3,... )
        if(node)
        {   if(node->data == val)
                return node;
            for (int i = node->children.size() - 1; i >= 0; --i)
                openlist.push(node->children[i]);
        }
    }

    return nullptr; // failed
}

// iterative implementation of BFS
// simple change from tree_depth_first_search_iter (previous)
// change container type to deque
template <typename T>
TNode<T> const *        // returns first found node that is equal to val
tree_breadth_first_search_iter( TNode<T> const * pRoot, T const & val )
{
    std::deque<TNode<T>*> openlist;
    openlist.push_back(const_cast<TNode<T>*>(pRoot));

    while ( openlist.size() > 0 ) {
        TNode<T>* node = openlist.back();
        openlist.pop_back();

        // insert children in the order ( 0,1,2,3,... )
        // reverse to make it "left-to-right"
        if(node)
        {
            if(node->data == val)
                return node;
            openlist.insert(openlist.cbegin(), node->children.rbegin(), node->children.rend());
        }
    }
    return nullptr; // failed
}

#endif
