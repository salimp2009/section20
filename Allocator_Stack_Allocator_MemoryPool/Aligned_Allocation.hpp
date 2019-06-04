#ifndef _ALLIGNED_ALLOC_H
#define _ALLIGNED_ALLOC_H
#include <cstddef>

// Aligned allocation function;
// 'align' argument must be a power of 2
// (typically 4, 6 or16)

typedef  uint8_t        U8;                // unsigned 8 bit integer; 1byte
typedef std::uintptr_t  ptrdiff;            // unsigned integer used for pointer arithmetics


// Shift the given address upwards if/as neccessary to
// ensure it is aligned to the number of given bytes
inline std::uintptr_t AlignAddress(std::uintptr_t addr, std::size_t align )
{
    const std::size_t mask = align-1;
    assert((align & mask)==0);          // check to make sure it is power of 2
    return (addr + mask)& ~mask;
}

// Shift the given pointer upwards if/as neccessary
// to ensure it is aligned to the given number of bytes
template<typename T>
inline T* AlignPointer(T* ptr, std::size_t align)
{
    const std::uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);   // allocated raw memory address converted to unsigned integer
    const std::uintptr_t addrAligned = AlignAddress(addr, align);   // send addr of raw memory to AlignAddress to do the alignment and move it upwards
    return reinterpret_cast<T*>(addrAligned);                       // recast the realignmemory from integer to pointer 
                                                                    // and return the address of the aligned memory
}

// Aligned Allocation function
// 'align' must be a power of 2 (typically 4,8, or 16)
void* AllocAlligned(std::size_t bytes, std::size_t align)
{
    // Allocate 'align' more bytes than we need
    std::size_t actualBytes = bytes + align;
    
    // Allocate unaligned block
    U8* pRawMem = new U8[actualBytes];
    
    // Align the block. if no alignment occured,
    // shift it up the full 'align' bytes so we
    // always have room to store the shift
    U8* pAlignedMemory = AlignPointer(pRawMem, align);
    if(pAlignedMemory==pRawMem)
        pAlignedMemory+=align;
        
    // Determine the shift and store it
    // Works for upto 25-byte alignment
    std::ptrdiff_t shift = pAlignedMemory - pRawMem;
    assert(shift >0 && shift <256);
    pAlignedMemory[-1]=static_cast<uint8_t>(shift & 0xFF);  // storing the shift preceding the 
    return pAlignedMemory;
}


#endif // _ALLIGNED_ALLOC_H