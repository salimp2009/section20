#ifndef _STACK_ALLOCATOR_H
#define _STACK_ALLOCATOR_H

#include <cstddef>
#include <memory>
#include <limits>
#include <new>
#include <memory>
#include "StackMemoryPool.hpp"

// Example for a StackAllocator that works as a wrapper to use Memory Pool Allocator
// this allocator and Memory pool allocates memory on the heap only once at the beginning
// everytime we add objects using this allocator then StackAllocator will use MemoryPool 
// allocate function to move the stack pointer up and assign a new address from the previosuly reserved memory
// everytime an object is deconstructed the pointer will be moved to a prrevious marker so we dont deallocated
// untill the whole memory is empty

// if the dellocation flag is changed to true then STL containers will not work since
// STL containers will try to deallocate evertime an object is deconstructed or delete which is not 
// efficient since it will ::free() or delete() will cause kernel interrupt and it will slow down the application
// for high performance applications like games, game engines....etc

/// Stack based allocator; Notes from ANKI Game Engine
///
/// @tparam T The type
/// @tparam deallocationFlag If true then the allocator will try to deallocate
///                          the memory. This is extremely important to
///                          understand when it should be true. See notes
/// @tparam alignmentBits Set the alighment in bits
///
/// @note The deallocationFlag can brake the allocator when the deallocations
///       are not in the correct order. For example when deallocationFlag==true
///       and the allocator is used in vector it is likely to fail.
///
/// @note Don't ever EVER remove the double copy constructor and the double
///       operator=. The compiler will create defaults


template<typename T, bool deallocationFlag=false, U32 alignmentBits=16>
class StackAllocator
{
    template<typename U, bool deallocationFlag_, U32 alignmentBits_>            // this is for moving another StackAllocator into here
    friend class StackAllocator;
    
public:
    // type definitions;
        typedef std::size_t      size_type;
        typedef std::ptrdiff_t   difference_type;
        typedef T*               pointer; 
        typedef const T*         const_pointer;
        typedef T&               reference;
        typedef const T&         const_reference;
        typedef T                value_type;
    
    // Default constructor
    StackAllocator() throw() { }
    
    // Copy Constructor
    StackAllocator(const StackAllocator& b) throw()
    {
        *this=b;
    }
    
    // Copy Constructor 
    template<typename U>
    StackAllocator(const StackAllocator<U, deallocationFlag, alignmentBits>& b) throw()
    {
        *this=b;
    }
    
    // Constructor with size
    StackAllocator(size_type size) throw()
    {
//        std::cout<<"Stack allocator working, size: "<<size<<'\n';
        mpool.reset(new StackMemoryPool(size, alignmentBits));              // reset the shared pointer mpool with creating a new memory with the given size
    }
    
    // Destructor
    ~StackAllocator(){}
    
    // Copy Assignment
    StackAllocator& operator=(const StackAllocator& b) 
    {
        mpool=b.mpool;
        return *this;
    }
    
    // Copy Assignment with different type
    template<typename U>
    StackAllocator& operator=(const StackAllocator<U, deallocationFlag, alignmentBits>& other) 
    {
        mpool=other.mpool;
        return *this;
    }
 
    // get the address of values
    pointer address(reference value) const 
    {
        return &value;
    }
        
    const_pointer address(const_reference value) const 
    {
        return &value;
    }
        
    pointer allocate(size_type n, const void* hint=0)
    {
        assert(mpool!=nullptr);    
        (void) hint;
        size_type size=n*sizeof(value_type);
            
        void* out = mpool->allocate(size);      // use Memory pool to allocate with the given size
        if(out!=nullptr) 
        {
//            std::cout<<"Stackallocator allocate working.."<<'\n';
        }
        else 
        {
            throw std::runtime_error("Allocation failed");
        }
        return (pointer)out;
        //return static_cast<T*>(out);
    }
        
    // Deallocate memory
    void deallocate(void* p, size_type n)
    {
        assert(mpool!=nullptr);
        (void)p;                        // not sure why we cast the this to from void* to void 
        (void)n;
            
        if(deallocationFlag)
        {
            bool ok=mpool->free(p);
            if(!ok) 
            {
                throw std::runtime_error("Freeing wrong pointer"
                    "De-Allocating on Stack Allocator should be in order..!!!\n");
            }
        }
    }
        
    // call constructor
    void construct(pointer p, const T& val)
    {   // placement new
        ::new((T*)p) T(val);           
    }
        
    // call constructor for multiple arguments
    template<typename U, typename... Args>
    void construct(U* p, Args&&...args)
    {
        ::new((void*)p) U(std::forward<Args>(args)...);
    }
        
    // Call destructor
    void destroy(pointer p)
    {
        p->~T();
    }
        
    // Call destructor for the other type
    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }
        
    // Get the max allocation size
    size_type max_size() const 
    {
        assert(mpool!=nullptr);
        return mpool->getSize();
    }
        
    // struct to rebind the allocator to another allocator of type U
    template<typename U>
    struct rebind
    {
        typedef StackAllocator<U, deallocationFlag, alignmentBits> other;  
    };
        
    // Reinitialize the allocator; all existing memory will be lost
    void reset()
    {
        assert(mpool!=nullptr);
        mpool->reset();
    }
        
    const StackMemoryPool& getMemoryPool() const
    {
        assert(mpool!=nullptr);
        return *mpool;
    }
        
private:
        std::shared_ptr<StackMemoryPool>mpool;
};

// Another allocator of the same type can deallocate this one
template<typename T1, typename T2, bool deallocationFlag, U32 alignmentBits>
inline bool operator==(const StackAllocator<T1, deallocationFlag, alignmentBits>&,
                       const StackAllocator<T2, deallocationFlag, alignmentBits>&) 
{
    return true;
}

// Another allocator of another type cannot deallocate from this one
template<typename T1, typename AnotherAllocator , bool deallocationFlag, U32 alignmentBits>
inline bool operator==(const StackAllocator<T1, deallocationFlag, alignmentBits>&,
                       const AnotherAllocator&) 
{
    return false;
}

// Another allocator of the same type can deallocate this one
template<typename T1, typename T2, bool deallocationFlag, U32 alignmentBits>
inline bool operator!=(const StackAllocator<T1, deallocationFlag, alignmentBits>&,
                       const StackAllocator<T2, deallocationFlag, alignmentBits>&) 
{
    return false;
}

// Another allocator of another type cannot deallocate from this one
template<typename T1, typename AnotherAllocator , bool deallocationFlag, U32 alignmentBits>
inline bool operator!=(const StackAllocator<T1, deallocationFlag, alignmentBits>&,
                       const AnotherAllocator&) 
{
    return true;
}
      
#endif // _STACK_ALLOCATOR_H