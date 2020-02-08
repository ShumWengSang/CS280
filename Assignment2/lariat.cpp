#include <iostream>
#include <iomanip>

#if 1
template <typename T, int Size>
std::ostream& operator<<( std::ostream &os, Lariat<T, Size> const & list )
{
    typename Lariat<T, Size>::LNode * current  = list.head_;
    int index = 0;
    while ( current ) {
        os << "Node starting (count " << current->count << ")\n";
        for ( int local_index = 0; local_index < current->count; ++local_index ) {
            os << index << " -> " << current->values[local_index] << std::endl;
            ++index;
        }
        os << "-----------\n";
        current = current->next;
    }
    return os;
}
#else // fancier 
#endif
