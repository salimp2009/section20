#ifndef _MYALLOC_H
#define _MYALLOC_H

#include <cstddef>
#include <memory>
#include <limits>
#include <new>

// Typical Allocator that works with STL Containers

extern std::size_t gAllocatedSize;

template<typename T>
class MyAlloc
{
public:
    // type definitions;
        typedef std::size_t      size_type;
        typedef std::ptrdiff_t   difference_type;
        typedef T*               pointer; 
        typedef const T*         const_pointer;
        typedef T&               reference;
        typedef const T&         const_reference;
        typedef T                value_type;
    
    //constructors
    // nothing to do; allocator has no state
    MyAlloc() throw() { }
    
    template<typename U>
    MyAlloc (const MyAlloc<U>&) throw() {} // no state to copy
    
    // destructor
    ~MyAlloc() throw() { }
    
    // Copy
    MyAlloc& operator=(const MyAlloc& b)
    {
        return *this=b;
    }
        
    // Copy with another type
    template<typename U>
    MyAlloc& operator=(const MyAlloc<U>& b)
    {
        return *this=b;
    }
 
    // allocate but dont initialize num elements of type T
    T* allocate (std::size_t num, const void* hint=0) {
        // allocate memory with global new
        gAllocatedSize+=num*sizeof(T);
        return static_cast<T*>(::operator new(num*sizeof(T)));
    }
    
    // deallocate storage of 
    void deallocate (T* p, std::size_t num) {
        // deallocate memory with global delete
        gAllocatedSize-=num*sizeof(T);
        ::operator delete(p);
    }
    
    // return the address of values
        pointer address(reference value) const 
        {
            return &value;
        }
        
        const_pointer address(const_reference value) const 
        {
            return &value;
        }
        
        // maximum number elements tht can be allocated
        size_type max_size() const throw() 
        {
             // return size_type(-1);
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
        
        // initialize elements of allocated storage of p with value type
        void construct(pointer p, const T& value) 
        {
           ::new((void*)p)T(value);
        }
        
        // constructor with multiple argumenets
        template<typename U, typename...Args>
        void construct(U* p, Args&&... args)
        {
            ::new((void*)p)U(std::forward<Args>(args)...);
        }
        
        // destroy elements of initiliazed storage p
        void destroy(pointer p) 
        {
            // destroy by calling their destructor
            p->~T();
        }
        
        // destroy pointer p with type U
        template<typename U>
        void destroy(U* p)
        {
            p->~U();
        }
        
        // rebind allocator to type U
        // rebind is used if we implement a container and have to allocate memory
        // for a type other than the element type; to implent a deque you need memory for
        // arrays that manage blocks of elements
        
        template<typename U>
        struct rebind 
        {
            typedef  MyAlloc<U> other;
        };
};

    //return that all specializations of this allocator are interchangeable
    template<typename T1, typename T2>
    bool operator==(const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept {
        return true;
    }
    
    template<typename T1, typename T2>
    bool operator!=(const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept {
        return false;
    }
    
#endif // _MYALLOC_H