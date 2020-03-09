#include "rummikub.h"
#include <iostream>
#include <map>
#include <algorithm>

bool CheckSolution(
        RummiKub & rks,
        std::vector< Tile > original_hand // copy
        )
{
    std::vector< std::vector< Tile > > runs     = rks.GetRuns();
    std::vector< std::vector< Tile > > groups   = rks.GetGroups();

    bool correct = true;
    // check tiles in solution are legal
    for( auto const& r : runs ) {
        for( Tile const& t : r ) {
            auto it = std::find_if( original_hand.begin(), original_hand.end(),
                    [&t]( Tile const& t1 ) {
                        return t.color == t1.color && t.denomination == t1.denomination;
                    } );
            if ( it == original_hand.end() ) {
                std::cout << "Tile " << t << " in solution was not in the original hand or duplicate\n";
                correct = false;
            } else {
                original_hand.erase( it );
            }
        }
    }
    for( auto const& g : groups ) {
        for( Tile const& t : g ) {
            auto it = std::find_if( original_hand.begin(), original_hand.end(),
                    [&t]( Tile const& t1 ) {
                        return t.color == t1.color && t.denomination == t1.denomination;
                    } );
            if ( it == original_hand.end() ) {
                std::cout << "Tile " << t << " in solution was not in the original hand or duplicate\n"; 
                correct = false;
            } else {
                original_hand.erase( it );
            }
        }
    }

    // check all tile were used in solution
    if ( original_hand.size() > 0 ) {
        for ( Tile const& t : original_hand ) {
            std::cout << "Tile " << t << " is not used in the solution\n"; 
            correct = false;
        }
    }

    //check groups are legal
    for( auto const& g : groups ) {
        unsigned long size = g.size();
        if ( size > 0 ) { // skip if empty
            if ( size < 3 || size > 4 ) {
                std::cout << "Group has incorrect size\n";
                correct = false;
            } else { // size is 3 or 4
                int denomination = g[0].denomination;
                std::map< Color, int > counts;
                for ( unsigned long i=0; i<size; ++i ) {
                    if ( g[i].denomination != denomination ) {
                        std::cout << "Group denominations do not match\n";
                        correct = false;
                    }
                    ++counts[ g[i].color ];
                }

                // check counts of colors
                for ( auto const& c : counts ) {
                    if ( c.second > 1 ) {
                        std::cout << "Group contains tiles of the same color\n";
                        correct = false;
                    }
                }
            }
        }
    }
    
    //check runs are legal
    for( auto const& r : runs ) {
        int counts[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 }; 

        Color color = r[0].color;

        for ( unsigned long i=0; i<r.size(); ++i ) {
            if ( r[i].color != color ) {
                std::cout << "Run colors do not match\n";
                correct = false;
            }
            ++counts[ r[i].denomination ];
        }

        for ( int const& c : counts ) {
            if ( c > 1 ) {
                std::cout << "Run contains tiles of the same denomination\n";
                correct = false;
            }
        }

        // 123--6789--- is a valid run 
        if ( correct ) {
            int len = 0;
            for ( int b : counts ) {
                if ( b ) { // is tile
                    if ( len>0 ) { // continued run
                        ++len;
                    } else { // new run started
                        len=1;
                    }
                } else { // no tile
                    if ( len>0 ) { // run ended
                        if ( len<3 ) { 
                            std::cout << "Run contains less than 3 tiles \n";
                            correct = false;
                        }
                        len=0; // not really necessary, see "len=1" above
                    } else { // no tile and no run going
                    }
                }
            }
            //check the length of the last run
            if ( counts[12] && len <3 ) {
                correct = false; 
                std::cout << "Run contains less than 3 tiles \n";
            }
        }
    }
    return correct;
}


void test0() // solvable
{
    RummiKub rks;
    std::vector< Tile > tiles;

    tiles.push_back( {1,Red} );    // run
    tiles.push_back( {2,Red} );
    tiles.push_back( {3,Red} );
    tiles.push_back( {3,Red} );
    tiles.push_back( {4,Red} );
    tiles.push_back( {5,Red} );



    std::random_shuffle( tiles.begin(), tiles.end() );
   
    for ( auto const& t : tiles ) {
        rks.Add( t );
    }

    rks.Solve();
    if ( CheckSolution( rks, tiles ) ) {
        std::cout << "Solved correctly\n";
    } else {
        std::cout << "Solved incorrectly\n";
    }
}

void test1() // solvable
{
    RummiKub rks;
    std::vector< Tile > tiles;

    tiles.push_back( {6,Yellow} ); // run
    tiles.push_back( {8,Yellow} );
    tiles.push_back( {7,Yellow} );
    tiles.push_back( {5,Red} );    // group
    tiles.push_back( {5,Blue} );
    tiles.push_back( {5,Green} );
    tiles.push_back( {5,Yellow} );
    tiles.push_back( {1,Red} );    // run
    tiles.push_back( {2,Red} );
    tiles.push_back( {3,Red} );
    tiles.push_back( {3,Red} );
    tiles.push_back( {4,Red} );
    tiles.push_back( {5,Red} );

    std::random_shuffle( tiles.begin(), tiles.end() );
   
    for ( auto const& t : tiles ) {
        rks.Add( t );
    }

    rks.Solve();
    if ( CheckSolution( rks, tiles ) ) {
        std::cout << "Solved correctly\n";
    } else {
        std::cout << "Solved incorrectly\n";
    }
}

void test2( ) 
{
    RummiKub rks;
    std::vector< Tile > tiles;

    tiles.push_back( {6,Yellow} );
    tiles.push_back( {8,Yellow} );
    tiles.push_back( {5,Green} );
    tiles.push_back( {5,Yellow} );
    tiles.push_back( {1,Red} );
    tiles.push_back( {2,Red} );
    tiles.push_back( {4,Red} );
    tiles.push_back( {5,Red} );

    std::random_shuffle( tiles.begin(), tiles.end() );
   
    for ( auto const& t : tiles ) {
        rks.Add( t );
    }

    rks.Solve();
    std::vector< std::vector< Tile > > runs     = rks.GetRuns();
    std::vector< std::vector< Tile > > groups   = rks.GetGroups();
    
    if ( runs.size()==0 && groups.size()==0 ) { // there is NO solution to this problem
        std::cout << "Solved correctly (no solution)\n";
    } else {
        std::cout << "Solved incorrectly (non-existing solution found)\n";
    }
}

#include <random>
std::vector< Tile >
GenerateRandomSolvable( 
        int num_runs, int max_run_length=13, 
        int num_groups = 0 
        )
{
    std::random_device                      rd;
    std::mt19937                            gen( rd() );
    std::uniform_int_distribution<int>      dis_group_denomination( 0,12 );  // random denomination
    std::uniform_int_distribution<int>      dis_group_length( 3,4 );         // random length 3 or 4
    std::uniform_int_distribution<int>      dis_run_color( 0,3 );            // random run color
    std::uniform_int_distribution<int>      dis_run_start( 0,10 );           // random run start
    std::uniform_int_distribution<int>      dis_rand( 0,10000000 );          // random number to be used in other cases

    std::vector< Tile > tiles;

    // create groups
    for ( int i=0; i<num_groups; ++i ) {
        int denomination    = dis_group_denomination( gen );
        int length          = dis_group_length( gen ); // 3 or 4
        if( length == 4 ) { // all 4 colors
            tiles.push_back( {denomination,Red} );
            tiles.push_back( {denomination,Green} );
            tiles.push_back( {denomination,Blue} );
            tiles.push_back( {denomination,Yellow} );
        } else { // one color to skip
            int color_to_skip = dis_rand( gen ) % 4;
            if ( Red    != color_to_skip ) { tiles.push_back( {denomination,Red} );     }
            if ( Green  != color_to_skip ) { tiles.push_back( {denomination,Green} );  }
            if ( Blue   != color_to_skip ) { tiles.push_back( {denomination,Blue} );    }
            if ( Yellow != color_to_skip ) { tiles.push_back( {denomination,Yellow} );  }
        }
    }
    //create runs
    for ( int i=0; i<num_runs; ++i ) {
        int start   = dis_run_start( gen );
        int end     = start + 3 + dis_rand( gen ) %  ( std::min(13,start+max_run_length)+1-3-start);
        //std::cerr << "create run from " << start << " to " << end << " of len " << end-start << std::endl;
        Color col   = static_cast<Color>( dis_run_color( gen ) );
        for ( int d=start; d<end; ++d ) {
            tiles.push_back( {d,col} );
        }
    }
    return tiles;
}

void test3() 
    // about 2*3.5 + 2*3.5 = 14 tiles on average 
    // two 2-tile or 4-tile groups
    // two 2-tile or 4-tile runs
    // expected time is 
{
    RummiKub rks;
    std::vector< Tile> tiles = GenerateRandomSolvable( 2, 4, 2);
    std::random_shuffle( tiles.begin(), tiles.end() );
   
    for ( auto const& t : tiles ) {
        rks.Add( t );
    }

    rks.Solve();
    //std::cout << "After Solve " << rks << std::endl;
    if ( CheckSolution( rks, tiles ) ) {
        std::cout << "Solved correctly\n";
    } else {
        std::cout << "Solved incorrectly\n";
    }
}


void (*pTests[])(void) = { 
	test0, test1, test2, test3
};

void test_all() {
	for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0]); ++i)
		pTests[i]();
}

#include <cstdio> /* sscanf */
int main( int argc, char *argv[] ) {
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
            //pTests[1]();
        } catch( const char* msg) {
            std::cerr << msg << std::endl;
        }
    }


    return 0;
}
