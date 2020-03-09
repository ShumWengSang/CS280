// TODO - check RouletteWheel - needs 9 positions
// upper_bound or lower_bound
// check find separately
// check find/compact on empty separately
#include <iostream>
#include <iomanip>
#include <algorithm>  // std::max_element
#include <functional> // std::bind std::placeholders
#include "lariat.h"
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// insert in the end
void test0()
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 5;
    Lariat<int, asize> lar;
    for( int i = 1; i <= 12; ++i ) {
        lar.insert( i-1, i );
        std::cout << lar << std::endl;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// insert in front
void test1()
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 1; i <= 14; ++i ) {
        lar.insert( 0, i );
        std::cout << lar << std::endl;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// insert in the middle 1
void test2()
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 8;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );

    for( int i = 1; i < 14; ++i ) {
        lar.insert( i, 4+i );
        std::cout << lar << std::endl;
    }
}

// insert in the middle 2
void test3()
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 7;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );

    for( int i = 1; i < 14; ++i ) {
        lar.insert( 2, 4+i );
        std::cout << lar << std::endl;
    }
}

// illegal insert 
void test4()
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 12;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );

    try {
        lar.insert( 5, 5 );
        std::cout << lar << std::endl;
    } catch ( LariatException & le ) {
        std::cout << "Somethingbad happened: " << le.what() << std::endl;
    }
}

void test5()
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 20;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );

    for( int i = 1; i < 14; ++i ) {
        lar.insert( 2, 4+i );
    }
    std::cout << lar << std::endl;
}

void test6() // delete middle - single node
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );
    std::cout << lar << std::endl;
    lar.erase( 1 );
    std::cout << lar << std::endl;
}

void test7() // delete front  - single node
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );
    std::cout << lar << std::endl;
    lar.erase( 0 );
    std::cout << lar << std::endl;
}

void test8() // delete last  - single node
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );
    std::cout << lar << std::endl;
    lar.erase( 3 );
    std::cout << lar << std::endl;
}

void test9() // delete middle - second node in list
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 4;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );
    lar.insert( 4, 5 );
    lar.insert( 5, 6 );
    std::cout << lar << std::endl;
    lar.erase( 4 );
    std::cout << lar << std::endl;
}

void test10() // delete front  - second node in list
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 4;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );
    lar.insert( 4, 5 );
    lar.insert( 5, 6 );
    std::cout << lar << std::endl;
    lar.erase( 3 );
    std::cout << lar << std::endl;
}

void test11() // delete last  - second node in list
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 4;
    Lariat<int, asize> lar;
    lar.insert( 0, 1 );
    lar.insert( 1, 2 );
    lar.insert( 2, 3 );
    lar.insert( 3, 4 );
    lar.insert( 4, 5 );
    lar.insert( 5, 6 );
    std::cout << lar << std::endl;
    lar.erase( 5 );
    std::cout << lar << std::endl;
}

void test12() // push_back push_front
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 4;
    Lariat<int, asize> lar;
    for( int i = 0; i < 11; ++i ) {
        lar.push_front( i );
    }
    for( int i = 0; i < 11; ++i ) {
        lar.push_back( 10+i );
    }
    std::cout << lar << std::endl;
}

void test13() // use index to print
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 11;
    Lariat<int, asize> lar;
    for( int i = 1; i <= 12; ++i ) {
        lar.insert( i-1, i );
    }
    std::cout << lar << std::endl;
    for( int i = 0; i < 11; ++i ) {
        std::cout << lar[i] << " ";
    }
    std::cout << std::endl;
}

void test14() // compact
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 0; i <= 17; ++i ) {
        lar.push_front( i+1 );
    }
    std::cout << "Before compacting" << std::endl;
    std::cout << lar << std::endl;
    lar.compact();
    std::cout << "After compacting" << std::endl;
    std::cout << lar << std::endl;
}

void test15() // compact and use
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 0; i <= 17; ++i ) {
        lar.push_front( i+1 );
    }
    std::cout << "Before compacting" << std::endl;
    std::cout << lar << std::endl;
    lar.compact();
    std::cout << "After compacting" << std::endl;
    std::cout << lar << std::endl;
    for( int i = 0; i <= 8; ++i ) {
        lar.push_front( i+10 ); //breaks here
        lar.push_back( i+10 );
    }
    std::cout << "After adding more elements" << std::endl;
    std::cout << lar << std::endl;
}

void test16() // compact and use find
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 0; i <= 17; ++i ) {
        lar.push_front( i+1 );
    }
    std::cout << "Before compacting" << std::endl;
    std::cout << lar << std::endl;
    lar.compact();
    std::cout << "After compacting" << std::endl;
    std::cout << lar << std::endl;
    for( int i = -1; i <= 19; ++i ) {
        unsigned pos = lar.find( i+1 );
        std::cout << "find " << i+1;
        if ( pos == lar.size() ) {
            std::cout << ":   not found " << std::endl;
        } else {
            std::cout << ":   position " << pos << std::endl;
        }
    }
}

void test17() // efficiency of push_back / pop_back
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 0; i < 1<<25; ++i ) {
        lar.push_back( i+1 );
    }
    std::cout << "Size = " << lar.size() << std::endl;
    for( int i = 0; i < 1<<25; ++i ) {
        lar.pop_back( );
    }
    std::cout << "Size = " << lar.size() << std::endl;

    lar.compact(); // compact empty lariat
}

void test18() // efficiency of find
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 0; i < 1<<15; ++i ) {
        lar.push_back( i+1 );
    }
    std::cout << "Size = " << lar.size() << std::endl;
    for ( unsigned i = 1<<14; i < 1<<15; ++i ) {
        if ( i != lar.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }
}

void test19() // copy ctor - basic tests
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 50; i < 100; ++i ) {
        lar.push_back( i+1 );
    }
    for( int i = 49; i >=0; --i ) {
        lar.push_front( i+1 );
    }
    std::cout << "Size = " << lar.size() << std::endl;

    Lariat<int, asize> lar_copy( lar );

    // check content of the copy
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar_copy.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }

    lar_copy.clear();
    std::cout << "Size = " << lar_copy.size() << std::endl;

    // check content of the original
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }
}

void test20() // assignment - basic tests
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar, lar2;
    for( int i = 50; i < 100; ++i ) {
        lar.push_back( i+1 );
        lar2.push_front( i+1 );
    }
    for( int i = 49; i >=0; --i ) {
        lar.push_front( i+1 );
        lar2.push_back( i+1 );
        lar2.push_front( 2*i+1 );
    }
    std::cout << "Size1 = " << lar.size() << std::endl;
    std::cout << "Size2 = " << lar2.size() << std::endl;

    lar2 = lar;
    std::cout << "Size2 = " << lar2.size() << std::endl;

    // check content of lar2
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar2.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }

    lar2.clear();
    std::cout << "Size2 = " << lar2.size() << std::endl;

    // check content of the original
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }
}

void test21() // copy ctor - different instantiations
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    for( int i = 50; i < 100; ++i ) {
        lar.push_back( i+1 );
    }
    for( int i = 49; i >=0; --i ) {
        lar.push_front( i+1 );
    }
    std::cout << "Size = " << lar.size() << std::endl;

    Lariat<float, 10> lar_copy( lar );

    // check content of the copy
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar_copy.find( static_cast<float>( i+1 ) ) ) {
            std::cout << "Find failed\n";
        }
    }

    std::cout << "Before clear " << lar_copy << std::endl;
    lar_copy.clear();
    std::cout << "Size = " << lar_copy.size() << std::endl;

    // check content of the original
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }
}

void test22() // assignment - different instantiations
{
    std::cout << "-------- " << __func__ << " --------\n";
    const int asize = 6;
    Lariat<int, asize> lar;
    Lariat<float, 11> lar2;
    for( int i = 50; i < 100; ++i ) {
        lar.push_back( i+1 );
        lar2.push_front( static_cast<float>( i+1 ) );
    }
    for( int i = 49; i >=0; --i ) {
        lar.push_front( i+1 );
        lar2.push_back( static_cast<float>( i+1 ) );
        lar2.push_front( static_cast<float>( 2*i+1 ) );
    }
    std::cout << "Size1 = " << lar.size() << std::endl;
    std::cout << "Size2 = " << lar2.size() << std::endl;

    lar2 = lar;
    std::cout << "Size2 = " << lar2.size() << std::endl;

    // check content of lar2
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar2.find( static_cast<float>( i+1 ) ) ) {
            std::cout << "Find failed\n";
        }
    }

    lar2.clear();
    std::cout << "Size2 = " << lar2.size() << std::endl;

    // check content of the original
    for ( unsigned i = 0; i < 50; ++i ) {
        if ( i != lar.find( i+1 ) ) {
            std::cout << "Find failed\n";
        }
    }
}

// stress testing
#include <tuple>
#include <map>
#include <vector>

enum Action { Insert, Pushback, Pushfront, Compact, Erase, Popback, Popfront, Index, Find };
//            <------- always OK ---------------->  <-- when non-empty ---->

#include <random>
class RouletteWheel {
    public:
        RouletteWheel()                                     = delete;
        RouletteWheel( RouletteWheel const& )               = delete;
        RouletteWheel( RouletteWheel && )                   = delete;
        RouletteWheel& operator=( RouletteWheel const& )    = delete;
        RouletteWheel& operator=( RouletteWheel && )        = delete;
        ~RouletteWheel()                                    = default;

        RouletteWheel( std::multimap< float, Action > const& _p, float _from, float _to ) 
            : p(_p ),
              gen( rd() ), 
              dis( _from, _to )
        { 
            for ( auto const& el : p ) {
                //std::cout << el.first << " --> " << el.second << std::endl;
                v.push_back( std::tuple<float, Action>( el.first, el.second ) );
            }
            //std::cout << "upper limit " << _to << std::endl;
        }

        Action Spin( )
        {
            return p.upper_bound( dis( gen ) )->second; // find key of the first element of the map that is >= rand_value
        }
    private:
        std::vector< std::tuple<float, Action> > v;
        std::multimap< float, Action > const&    p;
        std::random_device                       rd;
        std::mt19937                             gen;
        std::uniform_real_distribution<float>    dis;
};

class RandomNumber {
    public:
        RandomNumber()                                    = delete;
        RandomNumber( RandomNumber const& )               = delete;
        RandomNumber( RandomNumber && )                   = delete;
        RandomNumber& operator=( RandomNumber const& )    = delete;
        RandomNumber& operator=( RandomNumber && )        = delete;
        ~RandomNumber()                                   = default;

        RandomNumber( int _from, int _to ) :
              gen( rd() ), 
              dis( _from, _to ) 
        {}

        int GetInt( int max )
        {
            int rand_value = dis( gen );
            return rand_value % (max); // returns 0..max-1 inclusively
        }
    private:
        std::random_device                  rd;
        std::mt19937                        gen;
        std::uniform_int_distribution<>     dis;
};

class LariatScenario {
    public:
        LariatScenario()                                    = delete;
        LariatScenario( LariatScenario const& )               = delete;
        LariatScenario( LariatScenario && )                   = delete;
        LariatScenario& operator=( LariatScenario const& )    = delete;
        LariatScenario& operator=( LariatScenario && )        = delete;
        ~LariatScenario()                                   = default;
        LariatScenario( 
                int num_operations, int max_value,
                float insertF, float eraseF,        // relative frequences of the 9 operations
                float pushbackF, float pushfrontF,  // do not have to add up to 1
                float popbackF, float popfrontF,    // normalized by hand
                float compactF,
                float indexF,
                float findF) 
        {
            int current_size = 0; // need to know whether delete-like operations are allowed

            std::multimap< float, Action > probabilities;
            float TotalF = insertF + eraseF + pushbackF + pushfrontF + popbackF + popfrontF + compactF + indexF + findF;

//            probabilities[(insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF + popfrontF + indexF + findF) / TotalF ]    =  Find;
//            probabilities[(insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF + popfrontF + indexF ) / TotalF        ]    =  Index;
//            probabilities[(insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF + popfrontF) / TotalF                  ]    =  Popfront;
//            probabilities[(insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF ) / TotalF                             ]    =  Popback;
//            probabilities[(insertF + pushbackF + pushfrontF + compactF + eraseF) / TotalF                                         ]    =  Erase;
//            probabilities[(insertF + pushbackF + pushfrontF + compactF) / TotalF                                                  ]    =  Compact;
//            probabilities[(insertF + pushbackF + pushfrontF) / TotalF                                                             ]    =  Pushfront;
//            probabilities[(insertF + pushbackF) / TotalF                                                                          ]    =  Pushback;
//            probabilities[ insertF / TotalF                                                                                       ]    =  Insert;
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF + popfrontF + indexF + findF) / TotalF, Find ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF + popfrontF + indexF ) / TotalF       , Index ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF + popfrontF) / TotalF                 , Popfront ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF + compactF + eraseF + popbackF ) / TotalF                            , Popback ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF + compactF + eraseF) / TotalF                                        , Erase ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF + compactF) / TotalF                                                 , Compact ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF + pushfrontF) / TotalF                                                            , Pushfront ) );
            probabilities.insert( std::make_pair( (insertF + pushbackF) / TotalF                                                                         , Pushback ) );
            probabilities.insert( std::make_pair(  insertF / TotalF                                                                                      , Insert ) );

            RouletteWheel rw_all    ( probabilities, 0, 1 ); // roulette wheel with required frequencies for all actions
            float upper_limit_for_empty = (insertF + pushbackF + pushfrontF + compactF) / TotalF; // use instead of 1 if empty
            RouletteWheel rw_insert ( probabilities, 0, upper_limit_for_empty ); // roulette wheel with required frequencies for insert-like actions

            RandomNumber rn( 0, num_operations*num_operations ); // num_operations is more or less magic number in this context

            for ( int i=0; i<num_operations; ++i ) {
                Action action;
                if ( current_size == 0 ) { // only insert, pushes, compact are allowed
                    action = rw_insert.Spin( );
                } else {
                    action = rw_all.Spin( );
                }

                if ( action == Insert ) { // insert is legal at indicies 0..current_size inclusively
                    scenario.push_back( std::tuple< Action, int, int >( action, rn.GetInt( current_size+1 ), rn.GetInt( max_value ) ) );
                    ++current_size;
                } else if ( action == Erase ) { // erase is legal at indicies 0..current_size-1 inclusively
                    scenario.push_back( std::tuple< Action, int, int >( action, rn.GetInt( current_size ), 0 ) ); // value not used by operation
                    --current_size;
                } else if ( action == Pushfront || action == Pushback ) { 
                    scenario.push_back( std::tuple< Action, int, int >( action, 0, rn.GetInt( 100 ) ) ); // position not used by operation
                    ++current_size;
                } else if ( action == Popfront || action == Popback ) { 
                    scenario.push_back( std::tuple< Action, int, int >( action, 0, 0 ) ); // position and value not used by operation
                    --current_size;
                } else if ( action == Compact ){ 
                    scenario.push_back( std::tuple< Action, int, int >( action, 0, 0 ) ); // position and value not used by operation
                } else if ( action == Find ){ 
                    scenario.push_back( std::tuple< Action, int, int >( action, 0, rn.GetInt( 100 ) ) ); // value 
                } else if ( action == Index ){ 
                    scenario.push_back( std::tuple< Action, int, int >( action, rn.GetInt( current_size ), 0 ) ); // position 
                } else {
                    std::cout << "illegal operation\n";
                }
            }
        }

        friend std::ostream& operator<< (std::ostream& os, LariatScenario const & sc)
        {
            for ( auto const& op : sc.Get() ) {
                int     val = std::get<2>( op );
                int     pos = std::get<1>( op );
                Action  a   = std::get<0>( op );
                switch ( a ) { // use labels
                    case Insert:
                        os << "Insert";
                        break;
                    case Erase:
                        os << "Erase";
                        break;
                    case Pushback:
                        os << "Pushback";
                        break;
                    case Pushfront:
                        os << "Pushfront";
                        break;
                    case Popfront:
                        os << "Popfront";
                        break;
                    case Popback:
                        os << "Popback";
                        break;
                    case Compact:
                        os << "Compact";
                        break;
                    case Index:
                        os << "Index";
                        break;
                    case Find:
                        os << "Find";
                        break;
                }
                os << " " << pos << " " << val << std::endl;
            }
            return os;
        }

        friend std::istream& operator>> (std::istream& is, LariatScenario & sc)
        {
            sc.scenario.erase( sc.scenario.begin(), sc.scenario.end() );
            for ( std::string a_str; is >> a_str ;   ) {
                int pos = 0, val = 0;
                Action a;
                if( a_str == "Insert" ) {
                    a = Insert;
                    is >> pos >> val;
                } else if ( a_str == "Erase" ) {
                    a = Erase;
                    is >> pos;
                } else if ( a_str == "Pushback" ) {
                    a = Pushback;
                    is >> val;
                } else if ( a_str == "Pushfront" ) {
                    a = Pushfront;
                    is >> val;
                } else if ( a_str == "Popfront" ) {
                    a = Popfront;
                } else if ( a_str == "Popback" ) {
                    a = Popback;
                } else if ( a_str == "Compact" ) {
                    a = Compact;
                } else if ( a_str == "Index" ) {
                    a = Index;
                    is >> pos;
                } else if ( a_str == "Find" ) {
                    a = Find;
                    is >> val;
                } else {
// add NOOP?
                }
                sc.scenario.push_back( std::tuple< Action, int, int >( a, pos, val ) );
            }
            return is;
        }

        ////////////////////////////////////////////////////
        std::vector< std::tuple< Action, int, int > > const& 
            Get() const 
            {
                return scenario; 
            }

        void DrawStats( std::map< Action, std::string > & labels ) const // reference should be const, but std::map[] is complaining
        {
            // final frequencies
            std::map<Action, float> counts;
            for ( auto const& op : scenario ) {
                Action  a   = std::get<0>( op );
                counts[ a ] += 1.0f;
            }

            // normalization - longest label
            unsigned max_len = 0;
            for ( auto const& lbl : labels ) {
                if ( lbl.second.length() > max_len ) {
                    max_len = static_cast<unsigned>( lbl.second.length() );
                }
            }

            // normalization 80 symbols
            float max_freq = std::max_element( 
                    counts.begin(), counts.end(),
                    std::bind( std::less<float>(),
                        bind(&std::map<Action, float>::value_type::second, std::placeholders::_1),
                        bind(&std::map<Action, float>::value_type::second, std::placeholders::_2)) 
                    )->second;

            max_len += 1; // bar offset
            // print 
            std::cout << "Statistics\n";
            for ( auto const& el : counts ) {
                std::cout << std::left << std::setw( static_cast<int>( max_len ) ) << labels[ el.first ]
                    << std::setfill('+') << std::setw( static_cast<int>( el.second / max_freq  * static_cast<float>( 79 - max_len ) ) ) << "+" 
                    << std::setfill(' ') << std::endl; // should have saved fill from before and set it back, assume 'space'
            }
        }
    private:
        std::vector< std::tuple< Action, int, int > > scenario; // action, position, value
};

template < int nodesize >
void run_scenario_with_alotof_output // for debugging
(
    int   num_operations, 
    float insertF, float eraseF,        // relative frequences of the 9 operations
    float pushbackF, float pushfrontF,  // do not have to add up to 1
    float popbackF, float popfrontF,    // normalized by hand
    float compactF,
    float indexF,
    float findF
)
{
    LariatScenario sc( num_operations, 100,
            insertF, eraseF, pushbackF, 
            pushfrontF, popbackF, popfrontF, 
            compactF, indexF, findF);

    Lariat<int, nodesize> lar;
    for ( auto const& op : sc.Get() ) {
        int     val = std::get<2>( op );
        int     pos = std::get<1>( op );
        Action  a   = std::get<0>( op );
        switch ( a ) {
            case Insert:
                std::cout << "Insert at " << pos << " value " << val << std::endl;
                lar.insert( pos, val );
                break;
            case Erase:
                std::cout << "Erase at " << pos << std::endl;
                lar.erase( pos );
                break;
            case Pushback:
                std::cout << "Pushback " << " value " << val << std::endl;
                lar.push_back( val );
                break;
            case Pushfront:
                std::cout << "Pushfront " << " value " << val << std::endl;
                lar.push_front( val );
                break;
            case Popfront:
                std::cout << "Popfront " << std::endl;
                lar.pop_front();
                break;
            case Popback:
                std::cout << "Popback " << std::endl;
                lar.pop_back();
                break;
            case Compact:
                std::cout << "Compact " << std::endl;
                lar.compact();
                break;
            case Index:
                std::cout << "Index position " << pos << std::endl;
                lar[pos];
                break;
            case Find:
                std::cout << "Find " << val << ". Result " << lar.find( val ) << std::endl;
                break;
        }
        std::cout << lar << std::endl;
    }

    std::map< Action, std::string > labels = { 
        { Insert     , "Insert"     },
        { Pushback   , "Pushback"   },
        { Pushfront  , "Pushfront"  },
        { Compact    , "Compact"    },
        { Erase      , "Erase"      },
        { Popback    , "Popback"    },
        { Popfront   , "Popfront"   },
        { Index      , "Index"      },
        { Find       , "Find"       }
    };
    //sc.DrawStats( labels );
}

template < int nodesize >
void run_scenario_cmp_to_vector // for correctess
(
    int   num_operations, 
    float insertF, float eraseF,        // relative frequences of the 9 operations
    float pushbackF, float pushfrontF,  // do not have to add up to 1
    float popbackF, float popfrontF,    // normalized by hand
    float compactF,
    float indexF,
    float findF
)
{
    LariatScenario sc( num_operations, 2000, insertF, eraseF, pushbackF, pushfrontF, popbackF, popfrontF, compactF, indexF, findF);
    //std::cout << sc;
    
    Lariat<int, nodesize> lar;
    std::vector<int> v;
    for ( auto const& op : sc.Get() ) {
        int     val = std::get<2>( op );
        int     pos = std::get<1>( op );
        Action  a   = std::get<0>( op );
        switch ( a ) {
            case Insert:
                //std::cout << "Insert at " << pos << " value " << val << std::endl;
                lar.insert( pos, val );
                v.insert( v.begin()+pos, val );
                break;
            case Erase:
                //std::cout << "Erase at " << pos << std::endl;
                lar.erase( pos );
                v.erase( v.begin()+pos );
                break;
            case Pushback:
                //std::cout << "Pushback " << " value " << val << std::endl;
                lar.push_back( val );
                v.push_back( val );
                break;
            case Pushfront:
                //std::cout << "Pushfront " << " value " << val << std::endl;
                lar.push_front( val );
                v.insert( v.begin(), val );
                break;
            case Popfront:
                //std::cout << "Popfront " << std::endl;
                lar.pop_front();
                v.erase( v.begin() );
                break;
            case Popback:
                //std::cout << "Popback " << std::endl;
                lar.pop_back();
                v.pop_back( );
                break;
            case Compact:
                //std::cout << "Compact " << std::endl;
                lar.compact();
//                v.swap( std::vector<int>( v ) ); // swap needs a reference, temporary arg can only have const&
                std::vector<int>( v ).swap ( v );
                break;
            case Index:
                //std::cout << "Index " << std::endl;
                if ( lar[ pos ] != v[ pos ] ) {
                    std::cout << "Index failed at pos " << pos << std::endl;
                }
                break;
            case Find:
                //std::cout << "Find " << std::endl;
                int find_pos                        = lar.find( val );
                std::vector<int>::iterator find_it  = std::find( v.begin(), v.end(), val );
                if ( ( find_pos == -1 && find_it == v.end() )|| ( find_pos == static_cast<int>( find_it-v.begin() ) ) ) {}
                else {
                    std::cout << "Find failed for value " << val << std::endl;
                }
                break;
        }

        
        //compare lar and v after each operation
        if ( lar.size() == v.size () ) {
            for( unsigned i=0; i<lar.size(); ++i ) {
                // print both
                //std::cout << "Index " << i << "  " << lar[i] << "  " << v[i] << std::endl;
                if ( lar[i] == v[i] ) {}
                else {
                    std::cout << "values differ: lar[" << i << "] = " << lar[i] << "    v[" << i << "] = " << v[i] << std::endl;
                    std::cout << lar << std::endl;
                }
            }
        } else {
                    std::cout << "sizes differ: lar is " << lar.size() << " and v is " << v.size() << std::endl;
        }
    }
}

#include <chrono>
template < int nodesize >
void run_scenario_cmp_to_vector_time // optimizations
(
    int   num_operations, 
    float insertF, float eraseF,        // relative frequences of the 9 operations
    float pushbackF, float pushfrontF,  // do not have to add up to 1
    float popbackF, float popfrontF,    // normalized by hand
    float compactF,
    float indexF,
    float findF
)
{
    LariatScenario sc( num_operations, 200000, insertF, eraseF, pushbackF, pushfrontF, popbackF, popfrontF, compactF, indexF, findF);

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    Lariat<int, nodesize> lar;
    for ( auto const& op : sc.Get() ) {
        int     val = std::get<2>( op );
        int     pos = std::get<1>( op );
        Action  a   = std::get<0>( op );
        switch ( a ) {
            case Insert:
                lar.insert( pos, val );
                break;
            case Erase:
                lar.erase( pos );
                break;
            case Pushback:
                lar.push_back( val );
                break;
            case Pushfront:
                lar.push_front( val );
                break;
            case Popfront:
                lar.pop_front();
                break;
            case Popback:
                lar.pop_back();
                break;
            case Compact:
                lar.compact();
                break;
            case Index:
                lar[ pos ];
                break;
            case Find:
                lar.find( val );
                break;
        }
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Lariat: time elapsed " << elapsed_seconds.count() << std::endl;


    start = std::chrono::system_clock::now();
    std::vector<int> v;
    for ( auto const& op : sc.Get() ) {
        int     val = std::get<2>( op );
        int     pos = std::get<1>( op );
        Action  a   = std::get<0>( op );
        switch ( a ) {
            case Insert:
                v.insert( v.begin()+pos, val );
                break;
            case Erase:
                v.erase( v.begin()+pos );
                break;
            case Pushback:
                v.push_back( val );
                break;
            case Pushfront:
                v.insert( v.begin(), val );
                break;
            case Popfront:
                v.erase( v.begin() );
                break;
            case Popback:
                v.pop_back( );
                break;
            case Compact:
                std::vector<int>( v ).swap ( v );
                break;
            case Index:
                v[ pos ];
                break;
            case Find:
                std::find( v.begin(), v.end(), val );
                break;
        }
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cout << "Vector: time elapsed " << elapsed_seconds.count() << std::endl;

    // final comparison
    if ( lar.size() == v.size () ) {
        for( unsigned i=0; i<lar.size(); ++i ) {
            // print both
            //std::cout << "Index " << i << "  " << lar[i] << "  " << v[i] << std::endl;
            if ( lar[i] == v[i] ) {}
            else {
                std::cout << "values differ: lar[" << i << "] = " << lar[i] << "    v[" << i << "] = " << v[i] << std::endl;
                std::cout << lar << std::endl;
            }
        }
    } else {
        std::cout << "sizes differ: lar is " << lar.size() << " and v is " << v.size() << std::endl;
    }

    std::map< Action, std::string > labels = { 
        { Insert     , "Insert"     },
        { Pushback   , "Pushback"   },
        { Pushfront  , "Pushfront"  },
        { Compact    , "Compact"    },
        { Erase      , "Erase"      },
        { Popback    , "Popback"    },
        { Popfront   , "Popfront"   },
        { Index      , "Index"      },
        { Find       , "Find"       }
    };
    //sc.DrawStats( labels );
}

void test23()
{
    std::cout << "-------- " << __func__ << " --------\n";
    // this is a random scenario - no output provided
    // mostly for YOUR OWN debugging 
    run_scenario_with_alotof_output<6>( // node size
            40,     // num operations
            3, 1,   // insert, erase
            2, 2,   // pushfront, pushback
            1, 1,   // popfront, popback
            1,      // compact 
            1,      // index
            1       // find
            ); 
}

void test24()
{
    std::cout << "-------- " << __func__ << " --------\n";
    // this is random scenario
    // expected output - NONE
    // stress testing and correctness
    run_scenario_cmp_to_vector<100>( // node size
            100,      // num operations
            4, 1,       // insert, erase
            4, 2,       // pushfront, pushback
            1, 1,       // popfront, popback
            1,          // compact 
            1,          // index
            1           // find
            ); 
}

void test25()
{
    std::cout << "-------- " << __func__ << " --------\n";
    // this is random scenario - no output provided
    // mostly for your own speed testing
    // expected output - time, not used in grading
    run_scenario_cmp_to_vector_time<5000>( // node size
            200000,     // num operations
            2, 1,       // insert, erase
            1, 1,       // pushfront, pushback
            1, 1,       // popfront, popback
            1,          // compact 
            1,          // index
            1           // find
            ); 
}

// small test for valgrind
void test26()
{
    std::cout << "-------- " << __func__ << " --------\n";
    // this is random scenario
    // expected output - NONE
    // stress testing and correctness
    run_scenario_cmp_to_vector<10>( // node size
            200,      // num operations
            4, 1,       // insert, erase
            4, 2,       // pushfront, pushback
            1, 1,       // popfront, popback
            1,          // compact 
            1,          // index
            1           // find
            ); 
}


void (*pTests[])(void) = { 
	test0, test1, test2, test3, test4, test5, test6, 
	test7, test8, test9, test10, test11, test12, test13, 
	test14, test15, test16, test17, test18, test19, test20,
	test21, test22, test23, test24, test25, test26
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
