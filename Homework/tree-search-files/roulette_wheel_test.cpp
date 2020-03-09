//g++ -std=c++11 roulette_wheel_test.cpp
#include "roulette_wheel.h"
#include <iostream>
#include <map>

int main()
{
    enum MyAction { up, left, down, right };

    RouletteWheel< MyAction > rw;
    // frequencies do not have to add to 1 or 100 (or any other special number)
    // RouletteWheel will normalize them.
    rw.Sector( 50, up );
    rw.Sector( 25, left );
    rw.Sector( 10, down );
    rw.Sector( 15, right );

    std::map< MyAction, int > stat;
    int num_iter = 100000;
    for ( int i=0; i<num_iter; ++i ) {
        ++stat[ rw.Spin() ]; // collect statistics
    }

    // display statistics
    std::cout << "up    " << 100*static_cast<double>( stat[ up ] ) / num_iter    << "%" << std::endl;
    std::cout << "left  " << 100*static_cast<double>( stat[ left ] ) / num_iter  << "%" << std::endl;
    std::cout << "down  " << 100*static_cast<double>( stat[ down ] ) / num_iter  << "%" << std::endl;
    std::cout << "right " << 100*static_cast<double>( stat[ right ] ) / num_iter << "%" << std::endl;

}

