#include "successor.h"
#include <iostream>

void print_all( Node* root )
{
    // get min
    Node* min = root;
    while ( min->left ) {
        min = min->left;
    }
    INT key = min->key;

    // print all keys in order
    Node* s;
    do {
        s = successor( root,key );
        std::cout << "successor of " << key << " is ";
        if (s) {
            std::cout << s->key << std::endl; 
            key = s->key;
        } else { 
            std::cout << "NULL" << std::endl; 
        }

    } while ( s );
}

void test0()
{
    /*
              5
             / \
            3   7
           / \
          1   4
    */
    Node n1  {1}; // leaf
    Node n4  {4}; // leaf
    Node n3  {3,&n1,&n4};
    Node n7  {7}; // leaf
    Node n5  {5,&n3,&n7};
    n1.parent = &n3;
    n4.parent = &n3;
    n3.parent = &n5;
    n7.parent = &n5;

    Node* root = &n5;

    print_all( root );
}

void test1()
{
    /*           9
               /   \
              5     16
             / \    /  \
            3   7  10    20
           / \          /
          1   4       18
                       \
                        19
    */
    Node n1  {1}; // leaf
    Node n4  {4}; // leaf
    Node n7  {7}; // leaf
    Node n10 {10}; // leaf
    Node n19 {19}; // leaf
    Node n3  {3,&n1,&n4};
    Node n5  {5,&n3,&n7};
    Node n18 {18,nullptr,&n19};
    Node n20 {20,&n18};
    Node n16 {16,&n10,&n20};
    Node n9  {9,&n5,&n16};

    n1.parent = &n3;
    n4.parent = &n3;
    n3.parent = &n5;
    n7.parent = &n5;
    n5.parent = &n9;

    n19.parent = &n18;
    n18.parent = &n20;
    n20.parent = &n16;
    n10.parent = &n16;
    n16.parent = &n9;

    Node* root = &n9;
    
    print_all( root );
}

void test2() // same as test1 - just prints 1 extra line - number of data comparisons
{
    Node n1  {1}; // leaf
    Node n4  {4}; // leaf
    Node n7  {7}; // leaf
    Node n10 {10}; // leaf
    Node n19 {19}; // leaf
    Node n3  {3,&n1,&n4};
    Node n5  {5,&n3,&n7};
    Node n18 {18,nullptr,&n19};
    Node n20 {20,&n18};
    Node n16 {16,&n10,&n20};
    Node n9  {9,&n5,&n16};

    n1.parent = &n3;
    n4.parent = &n3;
    n3.parent = &n5;
    n7.parent = &n5;
    n5.parent = &n9;

    n19.parent = &n18;
    n18.parent = &n20;
    n20.parent = &n16;
    n10.parent = &n16;
    n16.parent = &n9;

    Node* root = &n9;
    
    print_all( root );
    
    std::cout << "INT comparisons " << INT::GetCounter() << std::endl;
}

void print_all2( Node2* root )
{
    // get min
    Node2* min = root;
    while ( min->left ) {
        min = min->left;
    }
    INT key = min->key;

    // print all in order
    Node2* s;
    do {
        s = successor2(root,key);
        std::cout << "successor2 of " << key << " is ";
        if (s) {
            std::cout << s->key << std::endl; 
            key = s->key;
        } else { 
            std::cout << "NULL" << std::endl; 
        }

    } while ( s );
}

void test3()
{
    // same tree as in test0 - but without parents
    Node2 n1  {1}; // leaf
    Node2 n4  {4}; // leaf
    Node2 n3  {3,&n1,&n4};
    Node2 n7  {7}; // leaf
    Node2 n5  {5,&n3,&n7};
    Node2* root = &n5;

    print_all2( root );
}

void test4()
{
    // same tree as in test3 - but without parents
    Node2 n1  {1}; // leaf
    Node2 n4  {4}; // leaf
    Node2 n7  {7}; // leaf
    Node2 n10 {10}; // leaf
    Node2 n19 {19}; // leaf
    Node2 n3  {3,&n1,&n4};
    Node2 n5  {5,&n3,&n7};
    Node2 n18 {18,nullptr,&n19};
    Node2 n20 {20,&n18};
    Node2 n16 {16,&n10,&n20};
    Node2 n9  {9,&n5,&n16};
    Node2* root = &n9;
    
    print_all2( root );
}

void test5() // same as test4 - just prints 1 extra line - number of data comparisons
{
    Node2 n1  {1}; // leaf
    Node2 n4  {4}; // leaf
    Node2 n7  {7}; // leaf
    Node2 n10 {10}; // leaf
    Node2 n19 {19}; // leaf
    Node2 n3  {3,&n1,&n4};
    Node2 n5  {5,&n3,&n7};
    Node2 n18 {18,nullptr,&n19};
    Node2 n20 {20,&n18};
    Node2 n16 {16,&n10,&n20};
    Node2 n9  {9,&n5,&n16};
    Node2* root = &n9;
    
    print_all2( root );

    std::cout << "INT comparisons " << INT::GetCounter() << std::endl;
}

void (*pTests[])() = { test0,test1,test2,test3,test4,test5 };

void test_all() {
    for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i) 
        pTests[i]();
}

#include <cstdio>   //sscanf
int main (int argc, char ** argv) {
    if (argc >1) {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        try {
            pTests[test]();
        } catch( const char* msg) {
            std::cerr << msg << std::endl;
        }
    }
    return 0;
}

