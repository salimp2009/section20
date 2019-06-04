#ifndef _MY_ALLOCATOR_H
#define _MY_ALLOCATOR_H

#include <cstddef>
#include <memory>
#include <limits>
#include <new>

// Typical Allocator that works with STL Containers

// Defining a global that holds the allocated size
extern std::size_t gAllocatedSize;

template <typename T>
class MyAllocator {
public:
        // type definitions;
        typedef std::size_t      size_type;
        typedef std::ptrdiff_t   difference_type;
        typedef T*               pointer; 
        typedef const T*         const_pointer;
        typedef T&               reference;
        typedef const T&         const_reference;
        typedef T                value_type;

        //constructors & destructors
        MyAllocator() throw() {}
        
        MyAllocator(const MyAllocator&) {}
        
        // copy constructor taking argumenet other MyAllocator type
        template<typename U>
        MyAllocator(const MyAllocator<U>&) {}
        
        // destructor
        ~MyAllocator() {}
        
        // Copy
        MyAllocator& operator=(const MyAllocator& b)
        {
             return *this=b;
        }
        
        // Copy with another type
        template<typename U>
        MyAllocator& operator=(const MyAllocator<U>& b)
        {
            return *this=b;
        }
        
        // Allocate memory    
        // MyAllocator but dont initialize num elements of type T
        T* allocate(std::size_t n, const void* hint=0) 
        {
            size_type size= n*sizeof(T);
            gAllocatedSize+=size;
            return static_cast<T*>(:: operator new(size));
        
            // return static_cast<pointer>(::malloc(size));
        }
        
        // deallocate storage p of deleted elements
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
            typedef  MyAllocator<U> other;
        };
};

template<typename T1, typename T2>
bool operator==(const MyAllocator<T1>&, const MyAllocator<T2>&) throw() {
    return true;
}

template<typename T1, typename T2>
bool operator!=(const MyAllocator<T1>&,  const MyAllocator<T2>&) throw() {
    return false;
}

#endif // _MY_ALLOCATOR_H