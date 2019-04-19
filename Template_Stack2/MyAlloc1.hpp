#ifndef _MYALLOC1_H
#define _MYALLOC1_H

template<typename T>
class MyAlloc
{
public:
    //type definitiona
    typedef T value_type;
    
    //constructors
    // nothing to do; allocator has no state
    MyAlloc() noexcept { }
    
    template<typename U>
    MyAlloc (const MyAlloc<U>&) noexcept {   } // no state to copy
    
    // allocate but dont initialize num elements of type T
    T* allocate (std::size_t num) {
        // allocate memory with global new
        return static_cast<T*>(::operator new(num*sizeof(T)));
    }
    
    // deallocate storage of 
    void deallocate (T* p, std::size_t num) {
        // deallocate memory with global delete
        ::operator delete(p);
    }
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
    
#endif // _MYALLOC1_H