#include "Stack1.hpp"
#include <iostream>
#include <vector>

// partial specialization of class Stack<> for pointers:

template<typename T>
class Stack<T*>
{
private:
    std::vector<T*>elems;
public:
    Stack() {}
    Stack(std::initializer_list<T*>ls): elems{ls} { }
    ~Stack() {std::cout<<"\nStack deleter working...\n";}
    
    std::vector<T*> get_vec() const {return elems;}  // returns the vector
    void push(T* elem);           // adds data into container to the back    
    T* pop();                           // pops and returns the last element (element is not in the container any more)
    T* top() const;                     // returns a copy of the top element (element still in the container)
    bool empty() const {
        return elems.empty();           // returns true if empty
    }
    
};



template<typename T>
void Stack<T*>::push(T* elem)
{
    elems.push_back(elem);              // append a copy the passed element
} 

template<typename T>
T* Stack<T*>::pop()
{
    assert(!elems.empty());           // check if container is empty or not
    T* p=elems.back();                // assign last element to temporary variable
    elems.pop_back();                 // remove the last element; pop
    return p;                         // return a copy of the last element by value;
}

template<typename T>
T* Stack<T*>::top() const
{
    assert(!elems.empty());
    return elems.back();    
}
