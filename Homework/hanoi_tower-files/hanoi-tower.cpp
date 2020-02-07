#include "hanoi-tower.h"

#include <sstream>      // std::stringstream
#include <iomanip>      // left,right,fill,setw - see handout
#include <stack>
#include <vector>
#include <numeric>

struct Disk {
	//Size will determine which disk is bigger or smaller. Goes from smallest (top) to biggest (bottom, largest)
	int size;
  
  Disk& operator= (int const &other) { size = other; return *this;} 
};

struct Peg {
  char name;
	std::stack<Disk> disks_on_peg;
  
  Peg(char name) : name(name), disks_on_peg(){}
};

class TowerOfHanoi
{
private:
	Peg Source = {'A'};
	Peg Destination = {'C'};
	Peg Temp = {'B'};

	int num_of_disks;
	std::vector<Disk> disk_array;

  template<typename CALLBACK>
	void Solve_Hanoi_Recursive(int n, Peg& Source, Peg& Destination, Peg& temp, CALLBACK fn);
  
  template<typename CALLBACK>
	void Move_Disks(Peg& source, Peg& destination, CALLBACK fn);
  
public:
  template<typename CALLBACK>
	void Solve_Hanoi(CALLBACK fn);
  
  void SetMode(int mode);

	TowerOfHanoi(int num_of_disks);
	~TowerOfHanoi();
};

template< typename CALLBACK >
void hanoi_tower_1( int n, CALLBACK cb ) 
{
    // hanoi_tower_1_rec( .... );
    TowerOfHanoi ToH(n);
    ToH.Solve_Hanoi(cb);
}

////////////////////////////////////////////////////////////////////////////////
template< typename CALLBACK >
void hanoi_tower_2( int n, CALLBACK cb ) 
{
    hanoi_tower_1( n, cb ); // if not doing extra credit just leave it like this
}

////////////////////////////////////////////////////////////////////////////////
template< typename CALLBACK >
void hanoi_tower_3( int n, CALLBACK cb ) 
{
    hanoi_tower_1( n, cb ); // if not doing extra credit just leave it like this
}

TowerOfHanoi::TowerOfHanoi(int num_of_disks) : num_of_disks(num_of_disks), disk_array(num_of_disks)
{
  std::iota(disk_array.begin(), disk_array.end(), 1);

	//Initialize pegs so that n will be at bottom and 0 will be at top
	for (int i = num_of_disks - 1; i >= 0; i--) {
		Source.disks_on_peg.push(disk_array[i]);
	}
}

TowerOfHanoi::~TowerOfHanoi()
{

}

template<typename CALLBACK>
void TowerOfHanoi::Solve_Hanoi(CALLBACK cb)
{
	Solve_Hanoi_Recursive(num_of_disks, Source, Destination, Temp, cb);
}

template<typename CALLBACK>
void TowerOfHanoi::Solve_Hanoi_Recursive(int currentSize, Peg& Source, Peg& Destination, Peg& temp, CALLBACK fn)
{
	if (currentSize == 1) {
		Move_Disks(Source, Destination, fn);
	}
	else {
		Solve_Hanoi_Recursive(currentSize - 1, Source, temp, Destination, fn);
		Move_Disks(Source, Destination, fn);
		Solve_Hanoi_Recursive(currentSize - 1, temp, Destination, Source, fn);
	}
}

template<typename CALLBACK>
void TowerOfHanoi::Move_Disks(Peg& Source, Peg& Destination, CALLBACK fn)
{
  int diskID = Source.disks_on_peg.top().size;
	Destination.disks_on_peg.push(Source.disks_on_peg.top());
	Source.disks_on_peg.pop();

  std::stringstream ss;
  ss << "move disk " << diskID << " from " << Source.name << " to " << Destination.name;
  fn(ss.str());
}
