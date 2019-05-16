#ifndef _MY_UNIQUE_PTR_H
#define _MY_UNIQUE_PTR_H

// BASIC UNIQUE_PTR implementation
// std::unique_ptr has more interface option but the main frame is same

template<typename T>
class my_unique_ptr {
private:
    T* _ptr{nullptr};
public:
    my_unique_ptr()=default;
    my_unique_ptr(T* ptr): _ptr{ptr} { }
    
    // Delete the pointer
    ~my_unique_ptr() { 
        std::cout<<"\nDeleter working...\n";
        delete _ptr;
        } 
    
    // Prevent Copies
    my_unique_ptr(const my_unique_ptr& )=delete;
    my_unique_ptr operator=(const my_unique_ptr&)=delete;
    
    // Transfer Ownership
    my_unique_ptr(my_unique_ptr&& rhs): _ptr{rhs._ptr} {
        rhs._ptr=nullptr;
    }
     
     my_unique_ptr& operator=(my_unique_ptr&& rhs)
    {
        _ptr=rhs._ptr;
        rhs._ptr=nullptr; 
        return *this;
    }
    
    T& operator*() const {return *(_ptr);}
    T* operator->() const {return _ptr;}
  
   operator bool() {return _ptr;}
};

#endif //_MY_UNIQUE_PTR_H