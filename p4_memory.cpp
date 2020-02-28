#include "MemoryAllocator.h"
#include <iostream>

int main()
{
    MemoryAllocator allocator;
    allocator.init();

    int* pi = static_cast<int*>(allocator.alloc(sizeof(int)));
    double* pd = static_cast<double*>(allocator.alloc(sizeof(double)));
    int* pa = static_cast<int*>(allocator.alloc(10 * sizeof(int)));

    allocator.dumpBlocks();
    allocator.dumpStat();

    allocator.free(pi);
    allocator.free(pd);
    allocator.free(pa);

    allocator.destroy();
}


