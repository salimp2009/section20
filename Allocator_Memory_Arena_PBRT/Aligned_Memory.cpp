#include "MemoryArena.hpp"

// Aligned Memory Allocation for different systems;
// this is not needed after c++17; 

void *AllocAlligned(std::size_t size)
{
    #if __STDC_VERSION>=201112L
        return aligned_alloc(PBRT_CACLE_LINE_SIZE), size);
    #else
    #ifdef _MSVC_VER
        return _aligned_malloc(size, PBRT_CACLE_LINE_SIZE);
    //#else
        // use API of Linux
       return memalign(PBRT_CACLE_LINE_SIZE, size);              // clang could not compile this; check otherwise no linux support
    #endif
    #endif
}

void FreeAligned(void *ptr)
{
    if(!ptr) return;
    #ifdef _MSVC_VER
        // use Windows specific API
        _aligned_free(ptr);
    #else
        free(ptr);
    #endif
}