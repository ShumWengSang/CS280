//
// Created by roland on 3/8/20.
//

#include "successor.h"
#include "node.h"

// Given a root, finds the minimum value of the binary tree
// by traversing to the left as much as possible.
static Node* FindMinimum(Node* pRoot)
{
    // Check if null
    if(!pRoot)
        return pRoot;
    // Check left
    while(pRoot->left != nullptr)
    {
        // Keep moving left.
        pRoot = pRoot->left;
    }
    // Left-most found, return it.
    return pRoot;
}

static Node2* FindMinimum2(Node2* pRoot)
{
    // Check if null
    if(!pRoot)
        return pRoot;
    // Check left
    while(pRoot->left != nullptr)
    {
        // Keep moving left.
        pRoot = pRoot->left;
    }
    // Left-most found, return it.
    return pRoot;
}

static Node* FindSuccesor(Node* node)
{
    // Go up to parent
    Node* parent = node->parent;
    if(parent == nullptr)
        return parent;

    // Check where we came from
    if(parent->right == node) // If from right side.
    {
        return FindSuccesor(parent);
    }
    else // We came from left side.
    {
        return parent;
    }
}

Node* successor(Node* pRoot, INT key)
{
    // We have found our key.
    if ( pRoot->key == key ) { // data comparison
        if (pRoot->right) // IF right pointer is not null
        {
            // Find the minimum in the sub-tree at right side.
            // Sub tree is leftest
            return FindMinimum(pRoot->right);
        }
        else // If Right is null...
        {
            return FindSuccesor(pRoot);
        }
    }

    if (pRoot->key > key)
    { // data comparison
        return successor( pRoot->left, key);
    }
    else
    {
        return successor( pRoot->right, key);
    }
}

static Node2* successor2_helper(Node2* pRoot, INT key, bool* found)
{
    if (pRoot->key == key)
    {
        if (pRoot->right)
        {
            // easy
            *found = true;
            return FindMinimum2(pRoot->right);
        }
        else
        {
            // ??????
            return pRoot;
        }
    }

    if (pRoot->key > key)
    {
        Node2* returner = successor2_helper(pRoot->left, key, found);
        if(*found)
            return returner;
        else
        {
            *found = true;
            return pRoot;
        }
        // returning from left
        // ??????
    }
    else
    {
        return successor2_helper(pRoot->right, key, found);
        // returning from right
        // ??????
    }
}

Node2* successor2(Node2* pRoot, INT key)
{
    bool found = false;
    Node2* result = successor2_helper(pRoot, key, &found);
    if(found)
        return result;
    else
        return nullptr;
}