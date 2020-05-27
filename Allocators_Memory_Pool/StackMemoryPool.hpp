#pragma once


#include <cstddef>       // for std::size_t, ptrdiff_t
#include <cstdlib>       // for std::malloc
#include <cstdint>
#include <cstdio>
#include <atomic>
#include <limits>
#include <type_traits>
#include <cassert>

    typedef std::uint32_t        U32;
    typedef std::uint8_t         U8;               
    typedef std::size_t          PtrSize ; 

class StackMemoryPool
{
  public:
    typedef std::uint32_t        U32;
    typedef std::uint8_t         U8;               
    typedef std::size_t          PtrSize ; 
                
    StackMemoryPool(PtrSize msize, U32 alignment=16);
    
    StackMemoryPool(StackMemoryPool&& other)
    { 
        *this=std::move(other); 
    }
    
    StackMemoryPool& operator=(StackMemoryPool&& other);
   
    StackMemoryPool(const StackMemoryPool& other)=delete;
    StackMemoryPool& operator=(const StackMemoryPool& other)=delete;
    
    ~StackMemoryPool();
    
    // get the preallocated total size of the pool
    PtrSize getSize() const
    {
        return memsize;
    }
    
    // get the current allocated size
    PtrSize getAllocatedSize() const;
    
    // allocate memory; return pointer to allocate memory or nullptr upon failure
    [[nodiscard]] void* allocate(PtrSize size);
    
    // if ptr is not the last allocation nothing will happen and return false
    // otherwise deallocation will happen and return true
    bool free(void* ptr) noexcept;
    
    // Re-initialize the pool; all allocated memory will be lost
    void reset();
    
private:
    // Pre-allocated memory chunck
    U8* memory{nullptr};
    
    // Size of preallocated memory-chunk
    PtrSize memsize{0};
    
    // Point to the top of memory/stack
    std::atomic<U8*>top{nullptr};       // thread safe
    
    // Alligment of allocations
    U32 alignmentBits;
    
    // Calculation of the aligned size of an allocation
    PtrSize calcAlignSize(PtrSize size) const;
};

// extra feature used in Anki-Game Engine to track current allocated memory
struct MemoryBlockHeader
{
    U32 size;   
};

StackMemoryPool::StackMemoryPool(PtrSize msize, U32 alignment):memsize{msize}, alignmentBits{alignment}
{
    assert(memsize>0);
    
    memory=static_cast<U8*>(::malloc(memsize));
    
    if(memory!=nullptr) 
    {
       top.store(memory); 
       std::printf("Memory successfull memsize: %0.2lu\n", memsize);
    }
    else
    {
        std::printf("malloc() failed....\n"); 
    }       
}

StackMemoryPool::~StackMemoryPool()
{
    if(memory!=nullptr)
    {
        ::free(memory);
    }
}

StackMemoryPool& StackMemoryPool::operator=(StackMemoryPool&& other)
{
    if(this!=&other)   // no assignment to itself
    {
        if(memory!=nullptr) // if memory is not empty; clear it
        {
            ::free(memory);
        }
        
        memory=other.memory;
        memsize=other.memsize;
        top.store(other.top.load());
        alignmentBits=other.alignmentBits;
        
        other.memory=nullptr;
        other.memsize=0;
        other.top.store(nullptr);
        other.alignmentBits=0;
    }
    return *this;
}

PtrSize StackMemoryPool::getAllocatedSize() const
{
    return top.load()-memory;
}

[[nodiscard]]void* StackMemoryPool::allocate(PtrSize size)
{
    // if memory==null then it is moved
    assert(memory!=nullptr);
    
    PtrSize alignedSize=calcAlignSize(size + sizeof(MemoryBlockHeader));
    assert(alignedSize<std::numeric_limits<U32>::max());
    
    U8* out=top.fetch_add(alignedSize);
    
    // check if there is enough memory
    if(out + alignedSize <=memory+memsize)
    {
        ((MemoryBlockHeader*)out)->size=alignedSize;
        out+=sizeof(MemoryBlockHeader);
    }
    else
    {
        // if error
        out=nullptr;
    }
    
    return out;
}
bool StackMemoryPool::free(void* ptr) noexcept
{
    assert(memory!=nullptr);
    
    U8* realptr=static_cast<U8*>(ptr)-sizeof(MemoryBlockHeader);
    assert(realptr>=memory && realptr<memory+memsize);
    
    // get blocksize
    U32 size=((MemoryBlockHeader*)realptr)->size;
    
    U8* expected=realptr+size;
    U8* desired=realptr;
    
    bool exchange=top.compare_exchange_strong(expected, desired);
    
    return exchange;
}

void StackMemoryPool::reset()
{
    assert(memory!=nullptr);
    top.store(memory);
}

PtrSize StackMemoryPool::calcAlignSize(PtrSize size) const
{
    return size + (size % (alignmentBits/8));
}
