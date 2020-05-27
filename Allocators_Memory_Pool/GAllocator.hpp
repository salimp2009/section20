#pragma once

// Another more detailed of sample General Allocator
// Compatible for STL Containers
// Working on a sample from ANKI 3D Game Enginee
// See StackAllocator and StackPool for a more custom Allocator

#include <cstddef>       // for std::size_t, ptrdiff_t
#include <cstdlib>       // for std::malloc

extern std::size_t totalAllocatedSize;

template<typename T>
class GAllocator
{
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
    
    GAllocator() noexcept {}
    GAllocator(const GAllocator&) noexcept {}
    
    template<typename U>
    GAllocator(const GAllocator<U>&) noexcept {}
    
    ~GAllocator() {}
    
    GAllocator& operator=(const GAllocator&) { return *this;}
    
    template<typename U>
    GAllocator& operator=(const GAllocator<U>&) { return *this;}
    
    pointer address(reference x) { return &x;}                          // not required since c++11
   
    const_pointer address(const_reference x) const { return &x;}        // not required since c++11
    
    // Allocate memory
    pointer allocate(size_type n, const void* hint=0)                    // const void* is a hint
    {
        size_type size=n*sizeof(T);
        totalAllocatedSize +=size;                                      // gAllocatodeSize is global value to track the total used memory
        //return (pointer)::malloc(size);
        return static_cast<pointer>(::malloc(size));
    // return static_cast<T*>(::operator new(n*sizeof(T)));             // default in STL
    }
    
    // DeAllocate Memory
    void deallocate(void* p, size_type n)
    {
        size_type size=n * sizeof(T);
        totalAllocatedSize -=size;
        ::free(p);
        // ::delete(p);                                                 // default in STL
    }
    
    void construct(pointer p, const T& value)
    {
        ::new(p) T(value);          
    }
    
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args)                // Check if this needs enable_if_t<is_covertible_v<U, T> and check is_invocable_v<U,Args...>
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
    
    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max();           // better to define as a constexpr define constant in a precompiled definitions file
    }
    
    template<typename U>
    struct rebind
    {
        typedef GAllocator<U> other;
    };
    
};