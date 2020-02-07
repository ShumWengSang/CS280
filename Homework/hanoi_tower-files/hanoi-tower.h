#ifndef HANOITOWER_H
#define HANOITOWER_H

template< typename CALLBACK >
void hanoi_tower_1( int n, CALLBACK cb );

////////////////////////////////////////////////////////////////////////////////
// output just numbers, no alignment required
template< typename CALLBACK >
void hanoi_tower_2( int n, CALLBACK cb );

////////////////////////////////////////////////////////////////////////////////
// see output and handout for alignment explanation
template< typename CALLBACK >
void hanoi_tower_3( int n, CALLBACK cb );

#include "hanoi-tower.cpp"
#endif
