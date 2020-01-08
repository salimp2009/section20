#ifndef _MEMORY_ARENA_H
#define _MEMORY_ARENA_H

#include "Global_Constants.hpp"
#include <list>
#include <utility>

// This is an Memory Arena example from pbr.org
// Allocating contigous memory at the begininng and all allocations for 
// individual elements will be thru here by pointer increment. 
// Eveytime a memory block is requested it will be taken out from the available blocks
// added to 
// Memory is freed only at the end

// Aligned Memory Allocation for different systems;
// this is not needed after c++17; 
void *AllocAlligned(std::size_t size);  // defined in Aligned_Memory.cpp

// template verion of Alligned Alloca to use custom define types, classes
// such as AllocAligned<Foo>(n)
template<typename T>
T *AllocAlligned(std::size_t count)
{
    return (T*)AllocAlligned(count * sizeof(T));
}

void FreeAligned(void*);  // defined in Aligned_Memory.cpp

class MemoryArena
{
public:
    MemoryArena(std::size_t blockSize=262144): blockSize{blockSize} { }
    
    ~MemoryArena() 
    {
        FreeAligned(currentBlock);
        for(auto& block:usedBlocks)
            FreeAligned(block.second);
        for(auto& block : availableBlocks)
            FreeAligned(block.second);        
    }
    void* Alloc(std::size_t nBytes)
    {
        /* this is only for compatibiltiy issues as the alignment requirement might change
        // from compiler to compiler and also might be machine specific otherwise alignment =16 byte
        // Most modern computer architectures impose alignment requirements on the positioning of objects in memory. 
        // For example, it is frequently a requirement that float values be stored at memory locations that are word aligned. 
        // To be safe, the implementation always hands out 16-byte-aligned pointers (i.e., their address is a multiple of 16).
        */
        #if __GNUC__ ==4 && __GNUC__MINOR__<9  // GCC compilers donot respect alignment until version 4.9.0;
            constexpr int align =alignof(::max_align_t);  
        #elif !defined(PBRT_HAVE_ALIGNOF)
            constexpr int align{16};
        #else
            constexpr int align=alignof(std::max_align_t);
        #endif
        
        // check to see if align is a power of 2; 
        // better to implemented in GLOBAL constant header file 
        assert((align & (align-1))==0);
        
        // round nbytes to minimum machine alignment
        nBytes = (nBytes + align-1) & ~(align-1);
        
        // add current block to usedBlocks list
        // when an allocation request is made MemoryArena will store
        // the pointer to currentblock of memory in usedblocks list so it is not lost later
        // when we call Reset(), we will be able to reuse the block for next series of allocations
        
        // if the currentBlockPos +nBytes is above the currentAllocSize
        // check currentBlock is valid memory and add to used Block list
        if(currentBlockPos + nBytes > currentAllocSize) 
        {
            if(currentBlock) 
            {
                usedBlocks.push_back(std::make_pair(currentAllocSize, currentBlock));
                currentBlock=nullptr;
            }
            // try to get the memory from the availableBlock list
            // if not then ask for a new memory
            for(auto iter =availableBlocks.begin(); iter!=availableBlocks.end(); ++iter) 
            {
                if(iter->first>=nBytes) 
                {
                    // if the available list have enough bytes then get those 
                    // delete that position from the available list
                    currentAllocSize =iter->first;
                    currentBlock=iter->second;
                    availableBlocks.erase(iter);
                    break;
                }
            }
            if(!currentBlock) {
                currentAllocSize =std::max(nBytes, blockSize);
                currentBlock=AllocAlligned<std::uint8_t>(currentAllocSize);
            }
            currentBlockPos=0;
        }
         void *ret =currentBlock + currentBlockPos;
         currentBlockPos +=nBytes;
         return ret;   
    }
    
    // if an array of object of type T requests memory allocation
    // the template type and size will be send thru Alloc function
    // bool runConstructor=1 is used if dynamic location is required otherwise,
    // stamdart Alloc() function of the Memory Arean will be called for nbytes = n * sizeof(T)
    // the returned void pointer will be casted to type T* pointer and will be returned
    template<typename T>
    T* Alloc(std::size_t n=1, bool runConstructor=1)
    {
        T* ret=(T*)Alloc(n*sizeof(T));
        if(runConstructor)
        {
            for(std::size_t i{0}; i<n; ++i)
            {
                new(&ret[i]) T();
            }
            return ret;
        }
    }
    
    // reset function uses STL list splice function to redirect the pointers in usedBlocks
    // into availableBlocks, therefore there will be no new dynamic allocation only usedBlocks will
    // be used unless the size exceeds total allocation size nBytes > Blocksize; 
    // this will be handled in Alloc() function
    void Reset()
    {
        currentBlockPos=0;
        availableBlocks.splice(availableBlocks.begin(), usedBlocks);
    }
    
    // to check TotalAllocated size we add currentAllocSize + all usedBlocks
    std::size_t TotalAllocated() const 
    {
        std::size_t total = currentAllocSize;
        for(const auto& alloc:usedBlocks)
            total+=alloc.first;
        for(const auto& alloc : availableBlocks)
            total+=alloc.first;
        return total;
    }
    
private:
    // delete copy constructor and copy assignment ; only constructor and destructor allowed
    MemoryArena(const MemoryArena& )=delete;
    MemoryArena& operator=(const MemoryArena&)=delete;
    
    const std::size_t blockSize;
    std::size_t currentBlockPos{0}, currentAllocSize{0};
    std::uint8_t *currentBlock{nullptr};
    std::list<std::pair<std::size_t, std::uint8_t *>> usedBlocks, availableBlocks;
};


template<typename T, int logBlockSize>
class BlockedArray
{
public:
    BlockedArray(int uRes, int vRes, const T *d=nullptr)
            : uRes(uRes), vRes(vRes), uBlocks(Roundup(uRes)>>logBlockSize) {
                
    int nAlloc = Roundup(uRes)*Roundup(vRes);
    data = AllocAlligned<T>(nAlloc);
    for(int i{0}; i<nAlloc; ++i)
        new(&data[i]) T();
    if(d)
        for(int v{0}; v<vRes; ++v)
            for(int u{0}; u<uRes; ++u)
                (*this)(u,v)=d[v*uRes + u];
    }
    
    constexpr int BlockSize() const {return 1<<logBlockSize;}
    int Roundup(int x) const {
        return (x + BlockSize()-1) & ~(BlockSize()-1);
    }
    
    int uSize() const { return uRes;}
    int vSize() const { return vRes;}
    ~BlockedArray() {
        for(int i{0}; i< uRes * vRes; ++i)
            data[i].~T();
        FreeAligned(data);
    }

    
    
private:
    T *data;
    const int uRes, vRes, uBlocks;
    
};


#endif //_MEMORY_ARENA_H