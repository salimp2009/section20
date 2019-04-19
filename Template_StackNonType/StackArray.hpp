#ifndef _STACK_ARRAY_H
#define _STACK_ARRAY_H

#include <array>
#include <cassert>


template<typename T, std::size_t Maxsize>
class Stack {
private:
    std::array<T, Maxsize>elems;               // elems array of type T with a size of Maxsize
    std::size_t numElems;                       // num of elements; counter
public:
        Stack();                         // array dont have default constructors; aggregate container
 //    ~Stack()=default;
    
    std::array<T, Maxsize>& get_array() ;
    void push(T const& elem);                 // add elements to array
    void pop();                               // remove the last element
    T const& top() const;                     // return last element; const reference
    bool empty() const {
        return numElems==0;                   // alternative elems.empty(); array support .empty()
    }
    
    std::size_t size() {                     // return the current number of elements
        return numElems;
    }
};

template<typename T, std::size_t Maxsize>
Stack<T,Maxsize>::Stack():numElems{0} { elems={0};} // if the array is not initialized, 
                                                   // elements have garbagge value at the beginning

template<typename T, std::size_t Maxsize>
std::array<T,Maxsize>& Stack<T, Maxsize>::get_array()  {
    return elems;
}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::push(T const& elem) {
    assert(numElems<Maxsize);
    elems[numElems]=elem;
    ++numElems;
}

template<typename T, std::size_t Maxsize>
void Stack<T, Maxsize>::pop() {
    assert(!elems.empty());
    --numElems;
}

template<typename T, std::size_t Maxsize>
T const& Stack<T, Maxsize>::top() const {
    assert(!elems.empty());
    return elems[numElems-1];
}

#endif //_STACK_ARRAY_H

