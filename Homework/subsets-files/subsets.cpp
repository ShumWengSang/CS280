
#include <set>
#include <algorithm>

// actual recursive function
template <typename T>
void subset_rec(std::vector<T> base, std::vector<T> const& set, typename std::vector<T>::size_type currentLength)
{
	if(currentLength == set.size())
	{
		std::cout << "{ ";
		for(typename std::vector<T>::size_type i = 0; i < base.size(); ++i)
		{
			std::cout << base[i] << " ";
		}
		std::cout << "}" << std::endl;
	}
	else
	{
		T toAdd = set[currentLength];
		std::vector<T> rightBase { base };
		rightBase.push_back(toAdd);
		
		subset_rec(rightBase, set, currentLength + 1);
		subset_rec(base, set, currentLength + 1);
	}
}

// kickstart
template< typename T >
void subsets( std::vector<T> const& set)
{
  // Print out all variations
  subset_rec(std::vector<T>(), set, 0);
  
}
