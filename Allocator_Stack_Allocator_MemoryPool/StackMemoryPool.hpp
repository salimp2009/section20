#ifndef _STACK_MEMORYPOOL_H
#define _STACK_MEMORYPOOL_H
#include <cstdint>
#include <limits>
#include <atomic>
#include <stdexcept>
#include <cassert>  // will be replace by a custom assert; to get a better error definition
#include <stdlib.h>

// Sample Memory Pool from Anki3d Game Engine
// This memory pool is a class that holds:

// - the preallocated memory,
// - a pointer to the top of the stack and
// - a few other things

// Excerpt from ANKI Blog;

// "When allocate() is been called the pool calculates the size of the block to allocate. 
// The block consists from a header (see MemoryBlockHeader) plus the requested memory. 
// The header consists from just a number, the size of the allocated bytes (including the header). 
// The size is kept because the free() will not be called with size just like the standard free().
//  Why call free() without size when the allocator’s deallocate() method passes the size? 
// Author's explanation;
// the StackMemoryPool does not need the block header if it’s been used only in allocators 
// but in AnKi it’s been used for other stuff as well. 
// ignore the block header from now on. 

// The free() decrements the top of the stack but in a thread-safe way.
//   the allocations and deallocations should happen in LIFO order. 
// If the requested deallocation in free() is not the last 
// then the top will not change and false will be returned. 
// The atomic operation compare_exchange_strong() is 
// essential for making the operation thread safe.


// The calcAlignSize() is been used to align the given size for reasons mentioned before"

// type definitions;
// std::ptrdiff_t is the signed integer type of the result of subtracting two pointers
        typedef std::size_t      Ptrsize;
        typedef std::ptrdiff_t   difference_type;  
        typedef  uint8_t         U8;
        typedef  uint32_t        U32;  

class StackMemoryPool
{
public:

    StackMemoryPool()=default;

    // Default Constructor
    StackMemoryPool(Ptrsize size, U32 alignmentBits=16);
    
    // Non-copyable; delete copy constructor and copy assignment
    StackMemoryPool(const StackMemoryPool&)=delete;
    StackMemoryPool& operator=(StackMemoryPool&)=delete;
    
    // Move constrctr
    StackMemoryPool(StackMemoryPool&& other)
    {
        *this=std::move(other);
    }
    
    // Move assignment
    StackMemoryPool& operator=(StackMemoryPool&& other);
    
    // Destructor
    ~StackMemoryPool();
    
    // Get total max allocation size of the memory pool
    Ptrsize getSize() const
    {
        return memsize;
    }
    
    // Get allocated size; (different then the getSize())
    Ptrsize getAllocatedSize() const;
    
    // Allocate Memory;
    // return the allocated memory or nullptr on failure
    void* allocate(Ptrsize size) throw();
    
    // Free memory in StackMemory Poll
    // if ptr is not the last allocation 
    // then nothing happens and return false
    // param[in] ptr Memory block to deallocate
    // return True if deallocation successfull and false otherwise
    bool free(void* ptr) throw();
    
    // Reinitialize the pool
    // All existing memory will be lost!!!
    void reset();
    
private:
    // Pointer to Pre-allocated memory chunk;
    U8* memory{nullptr};                // to get the address of the allocated memory
    
    // Size of the pre-allocated memory chunk
    Ptrsize memsize{0};                 // to get the size of the pool
    
    // Pointer to top of the stack
    std::atomic<uint8_t*>top{nullptr};      // address of the top of the stack = memory +sizeof(MemoryBlockHear) 
    
    // Alignment of allocation
    U32 alignmentBits;
    
    // Calculate the aligned size of an allocation
    Ptrsize calcAlignSize(Ptrsize size) const;
};

struct MemoryBlockHeader
{
  U32 size{0};  
};

StackMemoryPool::StackMemoryPool(Ptrsize size_, U32 alignmentBits_)
        :memsize{size_}, alignmentBits{alignmentBits_} 
{
        assert(memsize>0);
        memory=(U8*)::malloc(memsize);
        //memory=static_cast<uint8_t*>(::operator new(memsize));
        
        if(memory!=nullptr) {
            top=memory;
        }
        else
        {
            throw std::runtime_error("operator new failed");
        }
//        std::cout<<"Memory pool working, "<<", size: "<<memsize<<'\n';
}

StackMemoryPool::~StackMemoryPool()
{
    if(memory!=nullptr)
    {
        ::free(memory);
        //::operator delete(memory);
    }
//    std::cout<<"Stack Memory Pool Destructor: operator delete is working...."<<'\n';
}

StackMemoryPool& StackMemoryPool::operator=(StackMemoryPool&& other)
{
    if(memory!=nullptr) 
    {
        ::free(memory);
        //::operator delete(memory);
    }
    
    memory=other.memory;
    memsize=other.memsize;
    top.store(other.top.load());
    alignmentBits=other.alignmentBits;
    
    other.memory=nullptr;
    other.memsize=0;
    other.top=nullptr;   
 // other.top.store(nullptr);
    return *this;
}

Ptrsize StackMemoryPool::getAllocatedSize() const
{
    return top.load()-memory;                   // top = memory + MemoryBlockHeader::size
}

void* StackMemoryPool::allocate(Ptrsize size_) throw()
{
    // memory is nullptr if moved
    assert(memory!=nullptr);
    
    // total size = requested size_ + sizeof MemoryblockHeader 
    // and align this with calcAlignSize function
    Ptrsize size=calcAlignSize(size_ + sizeof(MemoryBlockHeader));
    
//    std::cout<<"Allocate ptrsize: "<<size<<", total allocated size: "<<this->getAllocatedSize()<<'\n';
    
    assert(size<std::numeric_limits<uint32_t>::max()&& "Too big allocation");
    U8* out=top.fetch_add(size);
    if(out + size <=memory + memsize) {             // the address of the top +size should be inside memory pool
        // Write the block header                   // then record the size in the MemoryBlock header
        ((MemoryBlockHeader*)out)->size=size;
        
        // Set the correct output
        out+=sizeof(MemoryBlockHeader);            
    }
    else
    {
        // Error
        out=nullptr;                            // if we are outside the memory pool then fail
    }
//    std::cout<<"Memory Pool working, size: "<<*out<<*top.load()<<'\n';
    return out;
}

bool StackMemoryPool::free(void* ptr) throw()
{
    // memory is nullptr if moved
    assert(memory!=nullptr);
    
    // Correct the p
    U8* realptr=(U8*)ptr-sizeof(MemoryBlockHeader);
    
    // realptr should be inside the  pool's preallocated memory
    assert(realptr>=memory && realptr <memory + memsize);
    
    // get the block size
    U32 size=((MemoryBlockHeader*)realptr)->size;
    
    // Atomic stuff
    U8* expected = realptr + size;
    U8* desired = realptr;
    
    bool exchange=top.compare_exchange_strong(expected, desired);
    
//    std::cout<<"Stack Memory Pool free function working...:"<<exchange<<'\n';
    
    return exchange;
}

void StackMemoryPool::reset()
{
    // memory is nullptr if moved
    assert(memory!=nullptr);
    top=memory;
    //top.store(memory);           // original top = memory ???
}

 Ptrsize StackMemoryPool::calcAlignSize(Ptrsize size) const 
 {
     return size +(size %(alignmentBits/8));
 }

#endif // _STACK_MEMORYPOOL_H