#ifndef _STACK4_H_
#define _STACK4_H_

#include <vector>
#include <cassert>

// Template with default Arguments

template<typename T, typename Cont=std::vector<T>>
class Stack
{
private:
    Cont elems;
    
public:
    Stack() { }
    Stack(std::initializer_list<T>ls) : elems{std::move(ls)} { }   
    Stack(T  elem): elems{std::move(elem)} { }                  // std::move is used for practice to prevent extra copies
    ~Stack() { }
    
    Cont const& get_vec() const {return elems;}                 // Cont const& used to make deque work for iterators & STL algorithms
    void push(T const& elem);
    T pop() ;
    T const& top() const;
    
    bool empty() const {
       return elems.empty(); 
    }
};



template<typename T, typename Cont>
void Stack<T, Cont>::push(T const& elem)
{
    elems.push_back(elem);    
}

template<typename T, typename Cont>
T Stack<T, Cont>::pop()
{
    assert(!elems.empty());
    T temp=elems.back();            // copy last element to temp
    elems.pop_back();               // remove last element from container
    return temp;                    // return a copy of the removed element
}

template<typename T, typename Cont>
T const& Stack<T, Cont>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

#endif //_STACK4_H_


