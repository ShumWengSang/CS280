#include "node.h"

int INT::counter = 0;

std::ostream& operator<<( std::ostream& os, INT const& val )
{
    os << val.data;
    return os;
}
