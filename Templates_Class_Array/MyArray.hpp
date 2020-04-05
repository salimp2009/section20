#ifndef _MY_ARRAY_H
#define _MY_ARRAY_H

#include <iostream>
#include <cassert>
//#include <initializer_list>                        // not used in this version
#define assertm(exp, msg) assert(((void)msg, exp))   // custom assert macro; disable in release mode


template<typename T, std::size_t N>
class MyArray
{
    std::size_t maxsize{N};
    T values[N];

public:    
    typedef std::size_t size_type;
    typedef T           value_type;
    
    MyArray()=default;
    MyArray(T n);                               // constructor to set initial values of all elements
    
    // MyArray(const MyArray& other)=default;  // copy constructor; compiler generator is OK
                                               // if user defined copy constructor is used compiler generated
                                               // move constructor and move assignment will be disabled and if it
                                               // is not explicitly intended dont do it ; will cause extra copy operations
    // element list initialization
    template<typename...U,
            typename=std::enable_if_t<(std::is_convertible_v<U, T> && ...)> > 
    MyArray(U&&... args):values{std::forward<U>(args)...} { } 
    
    T& operator[](std::size_t index) {
        //assert(index<N);                                      // works only in DEBUG build ; if RELEASE build is selected it is disabled
        assertm(index<N, "invalid access..beyond the range.."); // custom assert function for more expressive messages if needed; disabled in release mode
        return values[index];}

    const std::size_t size() const { return maxsize;}
    
    void fill(T n) { for(auto& value: values) value=n;}    
    
    friend std::ostream& operator<<(std::ostream& os, const MyArray& obj) {
        for(const auto& elem:obj.values)
            os<<elem<<" ";
        return os;
    }
    
};
 
 template<typename T, std::size_t N> 
 MyArray<T,N>::MyArray(T n){ 
        for(auto& value: values) value=n;
       // std::memset(values, n , sizeof values);
        }

#endif // _MY_ARRAY_H
