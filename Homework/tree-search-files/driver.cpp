#include <functional> // std::function
#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include "roulette_wheel.h" // random number with specific distribution
#include <random>
#include "tree2dot.h"       // print_dot (output tree in dot format) for debugging
#include "tree_search_1.h" // this lab stuff

// for example:
// distribution {1/4,1/4,1/4,1/4} creates complete tree with branching factor 4
// distribution {0,1} creates degenerate binary tree with all nodes having 1 right child
// distribution {1,0} creates degenerate binary tree with all nodes having 1 left child
// distribution {1/2,1/2} creates tree branching factor 3 mostly balanced
// cs330 empirical analysis problem? to do some estimations?
std::vector< std::tuple< TNode<int>*, int > >
//   vector               node  ->   depth
// for driver to be able to specialize the tree -- first node is root, level order
createRandomTree(
        unsigned n, // total number of nodes
        int min_val, int max_val,   // [min_val,max_val) - range for data
        std::vector< double >  prob_num_children    // 0 children 0.5 except 
        //      when current node is the 
        //      last possible node to have  
        //      children and current number of nodes 
        //      is less then $n$
        // 1 child    0.3
        // 2 child    0.2
        // should add up to 1

        )
{
    // roulette wheel for the number of children
    // one >=0 children (leaves are     allowed)
    // one >=1 children (leaves are NOT allowed)
    RouletteWheel< unsigned > rw_all, rw_non_leaf;
    for ( unsigned i=0; i<prob_num_children.size(); ++i ) {
        rw_all.Sector( prob_num_children[i], i );
    }
    for ( unsigned i=1; i<prob_num_children.size(); ++i ) {
        rw_non_leaf.Sector( prob_num_children[i], i );
    }

    // for data inside nodes
    std::random_device          rd;
    std::mt19937                gen( rd() );
    std::uniform_int_distribution<>  dis( min_val, max_val );

    // to keep track of the tree
    unsigned total_nodes = 0;
    unsigned current_level = 0;
    std::vector< std::tuple< TNode<int>*, int > > all_nodes;

    // create root
    TNode<int> * root = new TNode<int>;
    root->data = dis( gen );
    all_nodes.push_back( std::make_tuple( root, current_level ) ); // level 0

//    std::cout << "Root " << root << std::endl;
    bool done = ( ++total_nodes == n ); // are we done?

    // build tree level by level
    std::vector< std::tuple< TNode<int>*, int > > prev_level = all_nodes; // just root initially
    std::vector< std::tuple< TNode<int>*, int > > next_level;
    while ( not done ) {
        ++current_level;
        for ( unsigned i=0; i<prev_level.size() and not done; ++i ) {
            TNode<int>* parent = std::get<0>( prev_level[i] );
            unsigned num_children;
            if ( i+1 == prev_level.size() ) { // last node, but tree is not finished
                num_children = rw_non_leaf.Spin();              // >=1 children
            } else {
                num_children = rw_all.Spin();                   // >=0 children
            }
    
//            std::cout << "num_children " << num_children << std::endl;

            for ( unsigned j=0; j<num_children and not done; ++j ) {
                TNode<int>* child = new TNode<int>;
//                std::cout << "child " << child  << std::endl;
                child->data = dis( gen );
                next_level.push_back( std::make_tuple( child, current_level ) );
                parent->children.push_back( child );
                //all_nodes.push_back( std::make_tuple( child, current_level ) );
                done = ( ++total_nodes == n ); // are we done?
//                std::cout << "total_nodes " << total_nodes << "    n " << n << "      done " << done << std::endl;
            }
        }
        all_nodes.insert( all_nodes.end(), next_level.begin(), next_level.end() ); // add new nodes to all nodes
        prev_level = std::move( next_level ); // update levels
        next_level.clear();
    }

    return all_nodes;
}

// for testing, creates a random tree of specified size and branching factor
// children are distributed uniformly 0,...,branching_factor
// node values are uniform between 1 and 100
// value to search is 555, set by this function
template< typename SearchFunction >
void test_search_1_goal( unsigned tree_size, int branching_factor, SearchFunction funct )
{
    // basic tests: find using DFS, there is only 1 node with the specific value (555)
    std::vector<double> dist ( branching_factor, 1.0/branching_factor ); // b times 1/b
    std::vector< std::tuple< TNode<int>*, int > > nodes = createRandomTree( tree_size, 1, 100, dist );
    TNode<int> * pRoot = std::get<0>( nodes[0] );
    int val = 555;

    // to eliminate code duplication create lambda function
    auto test_search = [pRoot,val,funct]( TNode<int> * p_curr ) {
        // set specific node's data to val
        int save_val = val;
        std::swap( p_curr->data, save_val );
        // for debugging
//        print_dot( pRoot, 
//                std::cout, 
//                [](TNode<int> const * p_node)->int { return p_node->data; },
//                [](TNode<int> const * p_node)->std::vector<TNode<int>*> { return p_node->children; },
//                [val](TNode<int> const * p_node)->bool { return p_node->data==val; }
//                );
        // search for that val from the top
        TNode<int> const * res = funct( pRoot, val );
        // check if we found the right node
        if ( res == p_curr )  { std::cout << "OK\n"; } 
        else                    { std::cout << "Wrong\n"; }
        // reset
        std::swap( p_curr->data, save_val );
    };

    TNode<int> * p_curr; // pointer to pointer to node we are searching

    // change root to 555, find 555
    p_curr = pRoot;
    test_search( p_curr );

    // change last node to 555, find 555
    p_curr = std::get<0>( nodes.back() );
    test_search( p_curr );

    // change node in the middle to 555, find 555
    p_curr = std::get<0>( nodes[ nodes.size()/2 ] );
    test_search( p_curr );

    // several random positions
    std::random_device          rd;
    std::mt19937                gen( rd() );
    std::uniform_int_distribution<>  dis( 0, nodes.size()-1 );
    for ( int i=0; i<10; ++i ) {
        p_curr = std::get<0>( nodes[ dis( gen ) ] );
        test_search( p_curr );
    }

    // clean tree
    for ( auto p : nodes ) { delete std::get<0>(p); }
}

// 1 goal 
//                      n     b   search
// DFS recursive
void test0() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 20,   4,  tree_depth_first_search_rec<int> ); 
}
void test1() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 200,  6,  tree_depth_first_search_rec<int> ); 
}
void test2() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 2000, 10, tree_depth_first_search_rec<int> ); 
}

// DFS iterative
void test3() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 20,   4,  tree_depth_first_search_iter<int> ); 
}
void test4() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 200,  6,  tree_depth_first_search_iter<int> ); 
}
void test5() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 2000, 10, tree_depth_first_search_iter<int> ); 
}

// BFS iterative
void test6() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 20,   4,  tree_breadth_first_search_iter<int> ); 
}
void test7() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 200,  6,  tree_breadth_first_search_iter<int> ); 
}
void test8() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_1_goal( 2000, 10, tree_breadth_first_search_iter<int> ); 
}

// for testing, creates a random tree of specified size and branching factor
// children are distributed uniformly 0,...,branching_factor
// node values are uniform between 1 and 100
// value to search is 555, 
// this function sets 2 nodes to 555
// the node with smaller depth should be found first
template< typename SearchFunction >
void test_search_2_goals_bfs( unsigned tree_size, int branching_factor, SearchFunction funct )
//                       ===   <--- only for BFS
{
    // correctness tests: find using BFS, there is 2 nodes with the specific value (555)
    // one is optimal and one is suboptimal
    std::vector<double> dist ( branching_factor, 1.0/branching_factor ); // b times 1/b
    std::vector< std::tuple< TNode<int>*, int > > nodes = createRandomTree( tree_size, 1, 100, dist );
    TNode<int> * pRoot = std::get<0>( nodes[0] );
    int val = 555;

    // to eliminate code duplication create lambda function
    auto test_bfs = [pRoot,val,funct]( TNode<int> * p_curr1, TNode<int> * p_curr2 ) {
        //                                          should be
        //                                          found first
        // set specific nodes' data to val
        int save_val1 = val;
        std::swap( p_curr1->data, save_val1 );
        int save_val2 = val;
        std::swap( p_curr2->data, save_val2 );
        // for debugging
//        print_dot( pRoot, 
//                std::cout, 
//                [](TNode<int> const * p_node)->int { return p_node->data; },
//                [](TNode<int> const * p_node)->std::vector<TNode<int>*> { return p_node->children; },
//                [val](TNode<int> const * p_node)->bool { return p_node->data==val; }
//                );
        // search for that val from the top
        TNode<int> const * res = funct( pRoot, val );
        // check if we found the right node
        if ( res == p_curr1 )  { std::cout << "OK\n"; } 
        else                     { std::cout << "Wrong\n"; }
        // reset
        std::swap( p_curr1->data, save_val1 );
        std::swap( p_curr2->data, save_val2 );
    };

    // suboptimal goal - last node
    // optimal goal - right-most node on the previous level
    std::tuple< TNode<int>*, int > t1, t2;
    t2 = nodes.back(); // last node in the tree, suboptimal goal
    unsigned pos = nodes.size()-2;
    t1 = nodes[ pos ]; // looking for node that is above t2
    while ( pos>0 and std::get<1>( t1 ) >= std::get<1>( t2 ) ) { // walking nodes in reverse
        t1 = nodes[ --pos ];
    }

    if ( pos > 0 ) {
        test_bfs( std::get<0>( t1 ), std::get<0>( t2 ) );
    }

    // several random positions
    std::random_device          rd;
    std::mt19937                gen( rd() );
    std::uniform_int_distribution<>  dis( 0, nodes.size()-1 );
    int i =0;
    while( i<10 ) {
        std::tuple< TNode<int>*, int > t1 = nodes[ dis( gen ) ], t2 = nodes[ dis( gen ) ];
        if ( std::get<1>( t1 ) < std::get<1>( t2 ) ) {
            test_bfs( std::get<0>( t1 ), std::get<0>( t2 ) );
            ++i;
        }
    }
    // clean tree
    for ( auto p : nodes ) { delete std::get<0>(p); }
}

// BFS iterative correctness
void test9() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_bfs( 20,   4,  tree_breadth_first_search_iter<int> ); 
}
void test10() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_bfs( 200,  6,  tree_breadth_first_search_iter<int> ); 
}
void test11() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_bfs( 2000, 10, tree_breadth_first_search_iter<int> ); 
}

// for testing, creates a random tree of specified size and branching factor
// children are distributed uniformly 0,...,branching_factor
// node values are uniform between 1 and 100
// value to search is 555, 
// this function sets 2 nodes to 555
// the left node should be found first 
template< typename SearchFunction >
void test_search_2_goals_dfs( unsigned tree_size, int branching_factor, SearchFunction funct )
//                       ===   <--- only for DFS
// assumes that DFS traverses children left to right,
// i.e. goal in the left subtree is found before goal in the right
{
    // correctness tests: find using DFS, there is 2 nodes with the specific value (555)
    // one is optimal and one is suboptimal
    std::vector<double> dist ( branching_factor, 1.0/branching_factor ); // b times 1/b
    std::vector< std::tuple< TNode<int>*, int > > nodes = createRandomTree( tree_size, 1, 100, dist );
    TNode<int> * pRoot = std::get<0>( nodes[0] );
    int val = 555;

    // to eliminate code duplication create lambda function
    auto test_dfs = [pRoot,val,funct]( TNode<int> * p_curr1, TNode<int> * p_curr2 ) {
        //                                           should be
        //                                           found first
        // set specific nodes' data to val
        int save_val1 = val;
        std::swap( p_curr1->data, save_val1 );
        int save_val2 = val;
        std::swap( p_curr2->data, save_val2 );
        // for debugging
//        print_dot( pRoot, 
//                std::cout, 
//                [](TNode<int> const * p_node)->int { return p_node->data; },
//                [](TNode<int> const * p_node)->std::vector<TNode<int>*> { return p_node->children; },
//                [val](TNode<int> const * p_node)->bool { return p_node->data==val; }
//                );
        // search for that val from the top
        TNode<int> const * res = funct( pRoot, val );
        // check if we found the right node
        if ( res == p_curr1 )  { std::cout << "OK\n"; } 
        else                     { std::cout << "Wrong\n"; }
        // reset
        std::swap( p_curr1->data, save_val1 );
        std::swap( p_curr2->data, save_val2 );
    };

    std::random_device rd;
    std::mt19937       gen( rd() ); 

    // find first node with >1 children, 
    // choose one node from left (should be found first), one from right subtrees
    // even if node from left subtree is above the one from the right

    // find node with at least 2 children
    TNode<int> * p = std::get<0>( nodes[0] ); // root
    while ( p->children.size()<2 ) {
        if ( p->children.size() == 0 ) {
            std::cerr << "Degenerate tree - linked list\n";
            return;
        }
        // if here, "<2" and "not 0", therefore 1 child
        p = p->children[0];
    }

    // if here, p has >=2 children
    TNode<int> * p1 = p->children.front(); // left
    TNode<int> * p2 = p->children.back();  // right
    /* 
     *      p
     *    /   \
     *   p1   p2
     */

    // now move p1 all the way to a leaf
    while ( p1->children.size()>0 ) {
        p1 = p1->children[ std::uniform_int_distribution<int>( 0, p1->children.size()-1 ) ( gen ) ]; // random child
    }
    /* 
     *      p
     *    /   \
     *   .     p2
     *   |
     *   .
     *   p1
     */
    
    test_dfs( p1, p2 );

    // clean tree
    for ( auto p : nodes ) { delete std::get<0>(p); }
}

void test12() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_dfs( 20,   4,  tree_depth_first_search_rec<int> ); 
    test_search_2_goals_dfs( 20,   4,  tree_depth_first_search_rec<int> ); 
    test_search_2_goals_dfs( 20,   4,  tree_depth_first_search_rec<int> ); 
}
void test13() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_dfs( 200,  6,  tree_depth_first_search_rec<int> ); 
    test_search_2_goals_dfs( 200,  6,  tree_depth_first_search_rec<int> ); 
    test_search_2_goals_dfs( 200,  6,  tree_depth_first_search_rec<int> ); 
}
void test14() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_dfs( 2000, 10, tree_depth_first_search_rec<int> ); 
    test_search_2_goals_dfs( 2000, 10, tree_depth_first_search_rec<int> ); 
    test_search_2_goals_dfs( 2000, 10, tree_depth_first_search_rec<int> ); 
}

// DFS iterative
void test15() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_dfs( 20,   4,  tree_depth_first_search_iter<int> ); 
    test_search_2_goals_dfs( 20,   4,  tree_depth_first_search_iter<int> ); 
    test_search_2_goals_dfs( 20,   4,  tree_depth_first_search_iter<int> ); 
}
void test16() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_dfs( 200,  6,  tree_depth_first_search_iter<int> ); 
    test_search_2_goals_dfs( 200,  6,  tree_depth_first_search_iter<int> ); 
    test_search_2_goals_dfs( 200,  6,  tree_depth_first_search_iter<int> ); 
}
void test17() 
{ 
    std::cout << "-------- " << __func__ << " --------\n";
    test_search_2_goals_dfs( 2000, 10, tree_depth_first_search_iter<int> ); 
    test_search_2_goals_dfs( 2000, 10, tree_depth_first_search_iter<int> ); 
    test_search_2_goals_dfs( 2000, 10, tree_depth_first_search_iter<int> ); 
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void (*pTests[])(void) = { 
    // basic tests for all 3 searches - 1 goal only
    test0, test1, test2, // DFS recursive
    test3, test4, test5, // DFS iterative
    test6, test7, test8, // BFS
    // correctness tests - 2 goals, optimal and suboptimal - for BFS
    test9, test10, test11, 
    // correctness tests - 2 goals, left and right - for DFS
    test12, test13, test14, // recursive
    test15, test16, test17, // iterative
};

void test_all() {
    for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0]); ++i)
        pTests[i]();
}


#include <cstdio> /* sscanf */
int main(int argc, char *argv[] ) {
    if (argc >1) {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        try {
            pTests[test]();
        } catch( const char* msg) {
            std::cerr << msg << std::endl;
        }
    } else {
        try {
            test_all();
        } catch( const char* msg) {
            std::cerr << msg << std::endl;
        }
    }


    return 0;
}

//    std::vector<double> dist ( 4, 1.0/4 ); // 4 times 1/4
//    std::vector< std::tuple< TNode<int>*, int > > nodes = createRandomTree( 20, 1, 100, dist );
//
//    TNode<int> const * pRoot = std::get<0>( nodes[0] );
//    print_dot( pRoot, 
//            std::cout, 
//            [](TNode<int> const * p_node)->int { return p_node->data; },
//            [](TNode<int> const * p_node)->std::vector<TNode<int>*> { return p_node->children; },
//            [](TNode<int> const * p_node)->bool { return p_node->data<50 and p_node->data>20; } // do not mark any
//            );
