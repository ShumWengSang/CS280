#include <random>
#include <algorithm>
#include <iterator> // stream iterator
#include <numeric>  // iota


#include "avl-map.h"
#include <iostream>
#include <vector>
#include <cstdlib> 

void simple_inserts( CS280::AVLmap<int,int> & map, std::vector<int> const& data ) {
    //insert (using index operator) and perform sanity check each time
    for ( int const & key : data ) {
        map[ key ] = key; //value is not important
        // if you have the method below, uncomment next line
        // if (!map.sanityCheck()) std::cout << "Error\n";
    }
}

// rebalance right-right on insert at non-root node
void test0() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[5] = 5;
    map[2] = 2;
    map[8] = 8;
    map[9] = 9;
    std::cout << map << std::endl;
    map[10] = 10; // should cause rebalance at 8
    std::cout << map << std::endl;
}

// rebalance left-left on insert at non-root node
void test1() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[5] = 5;
    map[2] = 2;
    map[8] = 8;
    map[7] = 7;
    std::cout << map << std::endl;
    map[6] = 6; // should cause rebalance at 8
    std::cout << map << std::endl;
}

// rebalance left-right on insert at non-root node
void test2() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[5] = 5;
    map[2] = 2;
    map[10] = 10; 
    map[8] = 8;
    std::cout << map << std::endl;
    map[9] = 9; // should cause rebalance at 10
    std::cout << map << std::endl;
}

// rebalance right-left on insert at root node
void test3() { 
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[5] = 5;
    map[2] = 2;
    map[8] = 8; 
    map[10] = 10;
    std::cout << map << std::endl;
    map[9] = 9;  // should cause rebalance at 8
    std::cout << map << std::endl;
}

// rebalance right-right on insert at root node
void test4() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[8] = 8;
    map[9] = 9;
    std::cout << map << std::endl;
    map[10] = 10; // should cause rebalance at 8
    std::cout << map << std::endl;
}

// rebalance left-left on insert at root node
void test5() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[8] = 8;
    map[7] = 7;
    std::cout << map << std::endl;
    map[6] = 6; // should cause rebalance at 8
    std::cout << map << std::endl;
}

// rebalance left-right on insert at root node
void test6() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[10] = 10; 
    map[8] = 8;
    std::cout << map << std::endl;
    map[9] = 9; // should cause rebalance at 10
    std::cout << map << std::endl;
}

// rebalance right-left on insert at root node
void test7() { 
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[8] = 8; 
    map[10] = 10;
    std::cout << map << std::endl;
    map[9] = 9;  // should cause rebalance at 8
    std::cout << map << std::endl;
}

// the "tie"
// can only happen after delete
// only testing at the root
//
void test8() { 
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    map[5] = 5; 
    map[1] = 1;
    map[10] = 10;
    map[8] = 8;
    map[12] = 12;
    std::cout << map << std::endl;
    map.erase( map.find( 1 ) );  // should cause rebalance at 5
    // after delete the unbalance can be seen as 
    // either right-right or right-left
    // since right-right is cheaper - this is the correct way
    std::cout << map << std::endl;

    // similar test mirrored
    //CS280::AVLmap<int,int> map2;
    //map2[-5] = 5; 
    //map2[-1] = 1;
    //map2[-10] = 10;
    //map2[-8] = 8;
    //map2[-12] = 12;
    //std::cout << map2 << std::endl;
    //map2.erase( map2.find( -1 ) );  // should cause rebalance at 5
    //std::cout << map2 << std::endl;
}


////////////////////////////////////////////////
// implement basics of the iterator
// and find

void simple_finds( CS280::AVLmap<int,int> & map, std::vector<int> const& data ) {
    //insert all and perform sanity check each time
    for ( int const & key : data ) {
        CS280::AVLmap<int,int>::iterator it = map.find( key );
        if ( it == map.end() ) {
            std::cout << "cannot find value " << key << std::endl;
        }
    }
}

////////////////////////////////////////////////
// implement delete
void simple_deletes( CS280::AVLmap<int,int> & map, std::vector<int> const& data ) {
    //insert all and perform sanity check each time
    for ( int const & key : data ) {
        CS280::AVLmap<int,int>::iterator it = map.find( key );
        if ( it == map.end() ) {
            std::cout << "cannot find value " << key << std::endl;
        } else {
            map.erase( it );
            // if you have the method below, uncomment next line
            // if (!map.sanityCheck()) std::cout << "Error\n";
        }
    }

    //    std::cout << "--------------------\n" << map << std::endl;
}

// randomized, no output provided
void test9() {
    std::cout << "-------- " << __func__ << " --------\n";
    CS280::AVLmap<int,int> map;
    
    std::vector<int> data( 50 );
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    simple_inserts( map, data );
    std::cout << map << std::endl;

    // shuffle and find
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // shuffle and delete
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
    simple_deletes( map, data ); 

    std::cout << "Should be no output after this.\n" << map << std::endl;
}

////////////////////////////////////////////////
// a little more testing for inserts and deletes
// now mix inserts and deletes
// test is randomized, should produce no output
// check for crashes, check with valgrind
void inserts_delete_random( int N, int num_iter, 
        int min_number_to_insert, int max_number_to_insert, //min_number_to_insert < max_number_to_insert
        float ratio_to_delete, // 0..1
        bool perform_checks // false - speed only, true - mostly correctness
        ) {
    CS280::AVLmap<int,int> map;
    std::vector<int> data( N );   // data to insert (i.e. NOT in the map )
    std::iota( data.begin(), data.end(), 1 );
    std::vector<int> map_content; // initially empty 


    for ( int i=0; i<num_iter; ++i ) {
        // insert some number of elements
        std::random_device                      rd;
        std::mt19937                            gen( rd() );
        // number of elements to insert, min of 
        std::uniform_int_distribution<unsigned int>      dis( min_number_to_insert, max_number_to_insert );
        unsigned int num_insert = dis( gen );
        if ( num_insert > data.size() ) { num_insert = data.size(); }

//        std::cout << "insert " << num_insert << " elements\n";

        // insert from the back of shuffled data
        std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
//        std::copy( data.begin() + data.size() - num_insert, data.end(), std::ostream_iterator<int>(std::cout, " "));
//        std::cout << "\n";
        simple_inserts( map, std::vector<int>( data.begin() + data.size() - num_insert, data.end() ) );
        map_content.insert( map_content.end(), data.begin() + data.size() - num_insert, data.end() );
        data.resize( data.size() - num_insert );

        int num_delete = num_insert * ratio_to_delete;
//        std::cout << "delete " << num_delete << " elements\n";
        // delete some
        std::shuffle( map_content.begin(), map_content.end(), std::mt19937{std::random_device{}()} );
//        std::copy( map_content.begin() + map_content.size() - num_delete, map_content.end(), std::ostream_iterator<int>(std::cout, " "));
//        std::cout << "\n";
        simple_deletes( map, std::vector<int>( map_content.begin() + map_content.size() - num_delete, map_content.end() ) );
        data.insert( data.end(), map_content.begin() + map_content.size() - num_delete, map_content.end() );
        map_content.resize( map_content.size() - num_delete );

#if 0
        std::cout << "AVLmap size " << map.size() << "\n";
        std::cout << "---------------------------------------\n";
        std::cout << map << "\n";
        std::cout << "---------------------------------------\n";
#endif
        if ( perform_checks && map.size() != map_content.size() ) {
            std::cout << "Wrong size\n";
        }
    }

    if ( perform_checks ) {
        // check all data is in a tree
        for ( int const& el :  data ) {
            if ( map.find( el ) != map.end() ) {
                std::cout << "Error - found element that should not be in the tree\n";
            }
        }

        // check we can all data is in a tree
        for ( int const& el :  map_content ) {
            if ( map.find( el ) == map.end() ) {
                std::cout << "Error - not found\n";
            }
        }
    }
}

void test10() {
    std::cout << "-------- " << __func__ << " --------\n";
    inserts_delete_random( 1000, 10, 2, 12, 0.5, true );
}



// copy ctor basic tests
// expected output - none
void test11() {
    std::cout << "-------- " << __func__ << " --------\n";
    int N = 1000;
    CS280::AVLmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert some number of elements between N/2 and N
    std::random_device                              rd;
    std::mt19937                                    gen( rd() );
    std::uniform_int_distribution<unsigned int>     dis( N/2, N );
    data.resize( dis( gen ) );
    simple_inserts( map, data );

    // now copy the map
    CS280::AVLmap<int,int> map2( map );

    std::vector<int>::iterator it   = data.begin();
    std::vector<int>::iterator it_e = data.end();
    for ( ; it != it_e; ++it ) {
        // check copy
        CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );
        if ( it_map == map2.end() ) {
            std::cout << "Not found in a copy\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a copy, but value is wrong\n";
            }
        }
        
        // check original
        it_map = map.find( *it );
        if ( it_map == map.end() ) {
            std::cout << "Not found in a original\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a original, but value is wrong\n";
            }
        }
    }

}

// copy ctor basic tests 
// delete copy, check original
// expected output - none
void test12()
{
    std::cout << "-------- " << __func__ << " --------\n";
    int N = 1000;
    CS280::AVLmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    // insert N elements
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
    simple_inserts( map, data );

    {
        CS280::AVLmap<int,int> map2( map );
        // traverse data, find in copy
        std::vector<int>::iterator it   = data.begin();
        std::vector<int>::iterator it_e = data.end();
        for ( ; it != it_e; ++it ) {
            CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );

            if ( it_map == map2.end() ) {
                std::cout << "Not found in a copy\n";
            } else {
                if ( it_map->Value() != *it ) {
                    std::cout << "Found in a copy, but value is wrong\n";
                }
            }
        }
    } // map2 deleted


    // traverse data, find in original
    std::vector<int>::iterator it   = data.begin();
    std::vector<int>::iterator it_e = data.end();
    for ( ; it != it_e; ++it ) {
        CS280::AVLmap<int, int>::iterator it_map = map.find( *it );

        if ( it_map == map.end() ) {
            std::cout << "Not found in a original\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a original, but value is wrong\n";
            }
        }
    }

}

// copy ctor basic tests 
// delete original, check copy
// expected output - none
void test13()
{
    std::cout << "-------- " << __func__ << " --------\n";
    int N = 1000;
    CS280::AVLmap<int,int> * p_map = new CS280::AVLmap<int,int>;
    CS280::AVLmap<int,int> & map = *p_map;

    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    // insert N elements
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
    simple_inserts( map, data );

    CS280::AVLmap<int,int> map2( map );
    // traverse data, find in copy
    std::vector<int>::iterator it   = data.begin();
    std::vector<int>::iterator it_e = data.end();
    for ( ; it != it_e; ++it ) {
        CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );

        if ( it_map == map2.end() ) {
            std::cout << "Not found in a copy\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a copy, but value is wrong\n";
            }
        }
    }

    delete p_map;

    // traverse data, find in copy - again
    it   = data.begin();
    for ( ; it != it_e; ++it ) {
        CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );

        if ( it_map == map2.end() ) {
            std::cout << "Not found in a copy\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a copy, but value is wrong\n";
            }
        }
    }

}

// assignment basic tests
// expected output - none
void test14()
{
    std::cout << "-------- " << __func__ << " --------\n";
    // random map
    int N = 1000;
    CS280::AVLmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert some number of elements between N/2 and N
    std::random_device                              rd;
    std::mt19937                                    gen( rd() );
    std::uniform_int_distribution<unsigned int>     dis( N/2, N );
    data.resize( dis( gen ) );
    simple_inserts( map, data );

    // random map2
    CS280::AVLmap<int,int> map2;
    std::vector<int> data2( N );   // data to insert
    std::iota( data2.begin(), data2.end(), 1 );
    std::shuffle( data2.begin(), data2.end(), std::mt19937{std::random_device{}()} );

    // insert some number of elements between N/2 and N
    data2.resize( dis( gen ) );
    simple_inserts( map2, data2 );

    // now assign 
    map2 = map;

    std::vector<int>::iterator it   = data.begin();
    std::vector<int>::iterator it_e = data.end();
    for ( ; it != it_e; ++it ) {
        // check copy
        CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );
        if ( it_map == map2.end() ) {
            std::cout << "Not found in a copy\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a copy, but value is wrong\n";
            }
        }
        
        // check original
        it_map = map.find( *it );
        if ( it_map == map.end() ) {
            std::cout << "Not found in a original\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a original, but value is wrong\n";
            }
        }
    }
}

// assignment tests 
// delete assigned, check original
// expected output - none
void test15()
{
    std::cout << "-------- " << __func__ << " --------\n";
    int N = 2000;
    CS280::AVLmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert N elements
    simple_inserts( map, data );

    {
        int N2 = 200;
        CS280::AVLmap<int,int> map2;
        std::vector<int> data2( N2 );   // data to insert
        std::iota( data2.begin(), data2.end(), 1 );
        std::shuffle( data2.begin(), data2.end(), std::mt19937{std::random_device{}()} );
        // insert N elements
        simple_inserts( map2, data2 );
        map2 = map;

        std::vector<int>::iterator it   = data.begin();
        std::vector<int>::iterator it_e = data.end();
        for ( ; it != it_e; ++it ) {
            CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );

            if ( it_map == map2.end() ) {
                std::cout << "Not found in a assigned\n";
            } else {
                if ( it_map->Value() != *it ) {
                    std::cout << "Found in a assigned, but value is wrong\n";
                }
            }
        }
    } // map2 deleted


    // traverse data, find in original
    std::vector<int>::iterator it   = data.begin();
    std::vector<int>::iterator it_e = data.end();
    for ( ; it != it_e; ++it ) {
        CS280::AVLmap<int, int>::iterator it_map = map.find( *it );

        if ( it_map == map.end() ) {
            std::cout << "Not found in a original\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a original, but value is wrong\n";
            }
        }
    }
}

// assignment tests 
// delete original, check assigned
// expected output - none
void test16()
{
    std::cout << "-------- " << __func__ << " --------\n";
    int N = 2000;
    CS280::AVLmap<int,int> * p_map = new CS280::AVLmap<int,int>;
    CS280::AVLmap<int,int> & map = *p_map;

    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert N elements
    simple_inserts( map, data );

    int N2 = 200;
    CS280::AVLmap<int,int> map2;
    std::vector<int> data2( N2 );   // data to insert
    std::iota( data2.begin(), data2.end(), 1 );
    std::shuffle( data2.begin(), data2.end(), std::mt19937{std::random_device{}()} );
    // insert N elements
    simple_inserts( map2, data2 );

    map2 = map;

    std::vector<int>::iterator it   = data.begin();
    std::vector<int>::iterator it_e = data.end();
    for ( ; it != it_e; ++it ) {
        CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );

        if ( it_map == map2.end() ) {
            std::cout << "Not found in a assigned\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a assigned, but value is wrong\n";
            }
        }
    }

    delete p_map;

    // traverse data, find in assigned - again
    it   = data.begin();
    for ( ; it != it_e; ++it ) {
        CS280::AVLmap<int, int>::iterator it_map = map2.find( *it );

        if ( it_map == map2.end() ) {
            std::cout << "Not found in a assigned\n";
        } else {
            if ( it_map->Value() != *it ) {
                std::cout << "Found in a assigned, but value is wrong\n";
            }
        }
    }
}

// random inserts and deletes - stress test
// 100 times: insert between 20 and 200 and delete half of the number of inserted
// tree grows by average 90. 
// max size 200*100=20000
void test17() 
{
    std::cout << "-------- " << __func__ << " --------\n";
    inserts_delete_random( 20000, 100, 20, 200, 0.5, false );
}


void (*pTests[])(void) = 
{
    test0,test1,test2,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12,test13,
    test14,test15,test16,test17
};

int main(int argc, char **argv) 
{
    if (argc!=2) return 1;
    else {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        pTests[test]();
    }
    return 0;
} 
