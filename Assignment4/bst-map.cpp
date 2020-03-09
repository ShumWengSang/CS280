#pragma once
#include <iostream>
#include "bst-map.h"

namespace CS280
{
// static data members
    template<typename KEY_TYPE, typename VALUE_TYPE>
    typename CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator
            CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::end_it = CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator(nullptr);

    template<typename KEY_TYPE, typename VALUE_TYPE>
    typename CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const
            CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::const_end_it = CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const(
            nullptr);

// Node stuff
    template<typename KEY_TYPE, typename VALUE_TYPE>
    CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Node(KEY_TYPE k, VALUE_TYPE val, BSTmap::Node *p, int h, int b,
                                                    BSTmap::Node *l,
                                                    BSTmap::Node *r) : key(k), value(val), height(h), balance(b),
                                                                       parent(p),
                                                                       left(l), right(r)
    {

    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    KEY_TYPE const &CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Key() const
    {
        return key;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    VALUE_TYPE &CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Value()
    {
        return value;
    }

//in implementation file 
//method's name and return value have to be fully qualified with
//all required namespace and class names (like CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap)
//but the argument list does not have to be:
//function argument list automatically falls into the method's namespace (Koenig lookup)
    template<typename KEY_TYPE, typename VALUE_TYPE>
    CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap(const BSTmap &rhs) : // ....
    {
        // ...
    }

////////////////////////////////////////////////////////////
// typename is used to help compiler to parse
    template<typename KEY_TYPE, typename VALUE_TYPE>
    typename CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::begin()
    {
        if (pRoot) return BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator(pRoot->first());
        else return end_it;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::BSTmap_iterator(BSTmap::Node *p)
    {

    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    CS280::BSTmap::BSTmap_iterator&
    BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator=(const BSTmap::BSTmap_iterator &rhs)
    {
        return <#initializer#>;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    CS280::BSTmap::BSTmap_iterator &BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator++()
    {
        return <#initializer#>;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    BSTmap::BSTmap_iterator BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator++(int)
    {
        return BSTmap::BSTmap_iterator();
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    BSTmap::Node &BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator*()
    {
        return <#initializer#>;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    BSTmap::Node *BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator->()
    {
        return nullptr;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    bool BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator!=(const BSTmap::BSTmap_iterator &rhs)
    {
        return false;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    bool BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator==(const BSTmap::BSTmap_iterator &rhs)
    {
        return false;
    }





////////////////////////////////////////////////////////////
// do not change this code from here to the end of the file
/* figure out whether node is left or right child or root 
 * used in print_backwards_padded 
 */
    template<typename KEY_TYPE, typename VALUE_TYPE>
    char CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::getedgesymbol(const Node *node) const
    {
        const Node *parent = node->parent;
        if (parent == nullptr) return '-';
        else return (parent->left == node) ? '\\' : '/';
    }

/* this is another "ASCII-graphical" print, but using 
 * iterative function. 
 * Left branch of the tree is at the bottom
 */
    template<typename KEY_TYPE, typename VALUE_TYPE>
    std::ostream &CS280::operator<<(std::ostream &os, BSTmap<KEY_TYPE, VALUE_TYPE> const &map)
    {
        map.print(os);
        return os;
    }

    template<typename KEY_TYPE, typename VALUE_TYPE>
    void CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::print(std::ostream &os, bool print_value) const
    {
        if (pRoot)
        {
            BSTmap<KEY_TYPE, VALUE_TYPE>::Node *b = pRoot->last();
            while (b)
            {
                int depth = getdepth(b);
                int i;
                /* printf(b); */

                char edge = getedgesymbol(b);
                switch (edge)
                {
                    case '-':
                        for (i = 0; i < depth; ++i) std::printf("       ");
                        os << b->key;
                        if (print_value) { os << " -> " << b->value; }
                        os << std::endl;
                        break;
                    case '\\':
                        for (i = 0; i < depth; ++i) std::printf("       ");
                        os << edge << std::endl;
                        for (i = 0; i < depth; ++i) std::printf("       ");
                        os << b->key;
                        if (print_value) { os << " -> " << b->value; }
                        os << std::endl;
                        break;
                    case '/':
                        for (i = 0; i < depth; ++i) std::printf("       ");
                        os << b->key;
                        if (print_value) { os << " -> " << b->value; }
                        os << std::endl;
                        for (i = 0; i < depth; ++i) std::printf("       ");
                        os << edge << std::endl;
                        break;
                }
                b = b->decrement();
            }
        }
        std::printf("\n");
    }
}