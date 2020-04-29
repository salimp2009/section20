#ifndef _STACK_ARRAY_H_
#define _STACK_ARRAY_H_

#include <iostream>
#include <array>
#include <cassert>
#include <initializer_list>
#include <type_traits>



//template<typename T, std::size_t Maxsize>
template<typename T, auto Maxsize>
class Stack {
    using size_type=decltype(Maxsize);
private:
    std::array<T,Maxsize>elems;     // container to store the elements
    size_type numElems;            // current number of elements
public:
   Stack();
   void push(T elem);           
   void pop();
   T const& top() const&;
   bool empty() const {return numElems==0;}
   size_type size() const {return numElems;}
   
   friend std::ostream& operator<<(std::ostream& os, const Stack obj) {
       for(auto& elem:obj.elems)
           os<<elem<<" ";
       return os;
   }
   

    template<typename... U,
             typename=std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
    Stack(U&&... args):elems{std::forward<U>(args)...} { }

};

template<typename T, auto Maxsize>
Stack<T, Maxsize>::Stack(): numElems{0} { }

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::push(T elem) {
    assert(numElems<Maxsize);                // check the current num of elemes is smaller than Max size
    elems[numElems]=std::move(elem);
    ++numElems;                             // increment the element number for the next assignment
}

template<typename T, auto Maxsize>
void Stack<T, Maxsize>::pop() {
    assert(!elems.empty());
    --numElems;                             // decrease element number so the top element will be overwritten
}                                           

template<typename T, auto Maxsize>
T const& Stack<T, Maxsize>::top() const& {
    assert(!elems.empty());
    return elems[numElems-1];            // return the last element
}


#endif // _STACK_ARRAY_H_