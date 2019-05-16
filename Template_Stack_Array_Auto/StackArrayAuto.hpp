#ifndef _STACK_ARRAY_AUTO_H
#define _STACK_ARRAY_AUTO_H
#include <array>
#include <cassert>
#include <initializer_list>

// Example using auto in template parameters to determine the type 

template<typename T, auto MaxSize>                  
class Stack {
public:
        using size_type=decltype(MaxSize);
private:
    std::array<T, MaxSize>elems;
    size_type numElems;
public:
    Stack();
   // Stack(std::initializer_list<T>l): elems{l} { }  // initiliazer list did not work ; std::array did not accept
    void push(T const& elem);               // push a copy of element
    T pop();                                // remove the last element and return a copy 
    T const& top() const;                   // return a const reference to the last element
    bool empty() {return numElems==0;}      // return true if stack is empty
    
    size_type const size() const {return numElems;}  // return the current number of elements
};

//constructor
template<typename T, auto MaxSize>
Stack<T, MaxSize>::Stack(): numElems{0} { }   // starting with no elements

template<typename T, auto MaxSize>
void Stack<T,MaxSize>::push(T const& elem) {
    assert(numElems<MaxSize);         // check if numElems smaller than MaxSize
     elems[numElems]=elem;            // add the elem 
    ++numElems;                       // increase numElems 
}

template<typename T, auto MaxSize>
T Stack<T, MaxSize>::pop() {
    assert(!elems.empty());
    --numElems;
    T temp=elems[numElems];
    return temp;
}

template<typename T, auto MaxSize>
T const& Stack<T, MaxSize>::top() const {
    assert(!elems.empty());
    return elems[numElems-1];          // return a const ref to last element
}




#endif // _STACK_ARRAY_AUTO_H