#pragma once

#include "StackMemoryPool.hpp"
#include <memory>


// Notes from ANKI 3D;
// deallocationFlag; "...If the allocator is used in the propper LIFO way 
// then we can set this flag to 1, if we set it to 0 then the allocator will ignore deallocations 
// Why we ignore deallocations? This happens because the STL containers don’t work in a LIFO order 
// and trying to deallocate like that is for the most cases useless."

template<typename T, bool deallocationFlag=false, U32 alignmentBits=16>
class StackAllocator
{
    template<typename U, bool deallocationFlag_, U32 alignmentBits_>
    friend class StackAllocator;
    
public:
    // type definitions required for STL compatibility
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T               value_type;
    
    // Notes from Anki 3D: not sure how it works; need to search on cppreference;
    // Move assignments between containers will copy the allocator as well. If propagate_on_container_move_assignment
	// is not defined then not moves are going to happen.
    using propagate_on_container_move_assignment = std::true_type;
    
    // no args constructor
    StackAllocator() noexcept:mpool{std::make_shared<StackMemoryPool>()} {}
    // StackAllocator() noexcept:mpool{nullptr} {}     // Alternative using raw pointer
    // Copy Constructor
    StackAllocator(const StackAllocator& b) noexcept 
    {
            *this=b;
    }
    
    // Copy Constructor with a different type that is convertible & copyable
    // may need enable_if_t<> to prevent other copy const to be disabled
    template<typename U>
    StackAllocator(const StackAllocator<U, deallocationFlag, alignmentBits>& b) noexcept 
    {
        *this=b;
    }
    
    StackAllocator(size_type size) noexcept
    {
        mpool.reset(new StackMemoryPool(size, alignmentBits));
        //mpool=new StackMemoryPool(size, alignmentBits));              // alternative using raw pointer
    }
    
    ~StackAllocator() 
    {   
        // delete mpool;        // alternative using the raw pointer
    }
    
    StackAllocator& operator=(const StackAllocator& b) 
    {
        mpool=b.mpool;
        return *this;
    }
    
    template<typename U>
    StackAllocator& operator=(const StackAllocator<U, deallocationFlag, alignmentBits>& b)
    {
        mpool=b.mpool;
        return *this;
    }
    
    pointer address(reference x) const
    {
        return &x;
    }
    
    const_pointer address(const_reference x) const
    {
        return &x;
    }
    
    
    [[nodiscard]] pointer allocate(size_type n, const void* hint=0)
    {
        assert(mpool!=nullptr);
        (void) hint;
        size_type size = n * sizeof(value_type);
        void* out =mpool->allocate(size);
        
        if(out==nullptr)
        {
            printf("..Memory Allocation Failed....\n");
            return nullptr;  // if memory allocation fails..
        }
        // for debugging; add macro or #ifdef DEBUG
        std::printf("Allocated size: %lu\n", size);
        
        return static_cast<pointer>(out);
    }
    
    void deallocate(void* p, size_type n) noexcept
    {
        assert(mpool!=nullptr);
        (void)p;
        (void)n;
        bool ok = mpool->free(p);
        
        // free may return false if the atomic exchange return false since the top of the stack is being modified 
        // by a different thread; // need to refactor this to include a sequencing with a Spinlock or mutex instead of 
        if(!ok) 
        {
            std::printf("..Freeing Wrong Pointer..\nDe-allocations should be in order");
        }
    }
    
    void construct(pointer p, const T& val)
    {
        ::new(p) T(val);
    }
    
    template<typename U, typename...Args>
    void construct(U* p, Args...args)
    {
        ::new(static_cast<void*>(p)) U(std::forward<Args>(args)...);
    }
    
    void destroy(pointer p)
    {
        p->~T();
    }
    
    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }
    
    // get the max memory size
    size_type max_size() const
    {
        assert(mpool!=nullptr);
        return mpool->getSize();            // getSize() returns memory the pool which is initialized via constructor
    }
    
    template<typename U>
    struct rebind
    {
      typedef  StackAllocator<U, deallocationFlag, alignmentBits> other;  
    };
        
    void reset()
    {
        assert(mpool!=nullptr);
        mpool->reset();
    }
    
    const StackMemoryPool& getMemoryPool() const&
    {
        assert(mpool!=nullptr);
        return *mpool;
    }
    
private:
    std::shared_ptr<StackMemoryPool> mpool;             // author claims shared_pointer makes it thread safe but 
     
    // Alternative; no overhead and thread safe         // as of c++17 there is no atomic support for shared_ptr
    // if this alternative is used 
    //std::atomic<StackMemoryPool*> mpool               // but the StackMemoryPool has atomic memory that hold the data
                                                        // therefore it is thread_safe because the control block of the shared_ptr
                                                        // is already thread_safe per the library implementation
                                                        
};

template<typename T1, typename T2, bool deallocationFlag, U32 alignmentBits>
inline bool operator==(const StackAllocator<T1, deallocationFlag, alignmentBits>&, const StackAllocator<T2, deallocationFlag, alignmentBits>&)
{
    return true;
}

template<typename T1, typename AnotherAllocator, bool deallocationFlag, U32 alignmentBits>
inline bool operator==(const StackAllocator<T1, deallocationFlag, alignmentBits>&, const AnotherAllocator&)
{
    return true;
}

template<typename T1, typename T2, bool deallocationFlag, U32 alignmentBits>
inline bool operator!=(const StackAllocator<T1, deallocationFlag, alignmentBits>&, const StackAllocator<T2, deallocationFlag, alignmentBits>&)
{
    return false;
}

template<typename T1, typename AnotherAllocator, bool deallocationFlag, U32 alignmentBits>
inline bool operator!=(const StackAllocator<T1, deallocationFlag, alignmentBits>&, const AnotherAllocator&)
{
    return false;
}

