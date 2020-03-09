#include "catalan.h"

int catalan2(int size)
{
    if (size < 2) return 1;

    int n = 0;
    for (int s = 0; s < size; ++s)
    {
        //    left           right    (-1 is for root)
        //    subtree        subtree
        n += (catalan2(s) * catalan2(size - 1 - s));
    }
    return n;
}

int catalan3(int size)
{
    if (size < 2) return 1;

    int n = 0;
    int halfSize = size /2;
    for (int s = 0; s < halfSize; ++s)
    {
        for(int j = halfSize; j < size; ++j)
        {
            n += (catalan3(s) * catalan3(size - 1 - (s + j)));
        }
    }
    return n;
}

int catalan4(int size)
{
    (void)size;
    return 0;
}

int catalan(int size, int b)
{
    (void)size;
    (void)b;
    return 0;
}
