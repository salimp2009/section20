#ifndef _STACK1_H_
#define _STACK1_H_

#include <vector>
#include <cassert>
// #include <initializer_list>


// Template Class example from Book :"C++ Templates: Second Edition"
// Chapter 2.1

template<typename T>
class Stack
{
    
    friend std::ostream& operator<<(std::ostream& os, Stack<T> const& stack);
private:
    std::vector<T>elems;
public:
// if copy copy constructor and assignment constructor is provided
// then compiler does not use default constructor and destructors of vector type
// either provide them all or none...!!! Otherwise it gives a compiler error

//    Stack(Stack const&);            // copy constructor; inside the class definition we dont need to use template parameter for
//                                    // for Stack (class name) but outside the class definition template parameter has to be used 
//                                    // e.g: Stack<T> 
                                    
//    Stack& operator=(Stack const&);  // assignment operator
    
    Stack() {}
    Stack(std::initializer_list<T>l): elems(l) { }
    Stack(T elem) : elems({std::move(elem)}) { }
    ~Stack() { }
    
    std::vector<T> get_vec() const {return elems;}
    void push(T const& elem);   // push element
    T pop();                     // pop last element  
    T const& top() const;       // return top element
    bool empty() const {        // returns whether the stack
        return elems.empty();    // is empty or not     
    } 
    
};

Stack(char const*)->Stack<std::string>;


template<typename T>
void Stack<T>::push(T const& elem)  // outside the class definition the template parameter T has to be used with Stack<T>
{
    elems.push_back(elem);
}

template<typename T>
T Stack<T>::pop()
{ 
    assert(!elems.empty());     // check to see container not empty; it is used for exception safety
                                // if the container is empty asser calls std::abort and gets out of the function
    T last_elem =elems.back();  // assign temp to the last element of the container before removing it
    elems.pop_back();          // remove last elemnt
    return last_elem;           // return the copy of the last element (last element removed)
}

template<typename T>
T const& Stack<T>::top() const      // return top element
{
    assert(!elems.empty());       // Because assert is a function-like macro, commas anywhere in condition 
                                  // that are not protected by parentheses are interpreted as macro argument separators. 
                                  // Such commas are often found in template argument lists and list-initialization:
    return elems.back();
}

template<typename T>
bool operator==(Stack<T> const& obj1, Stack<T> const& obj2)
{
    return obj1.get_vec()==obj2.get_vec();   // just an example to show the use of template parameter outside class definition
    
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Stack<T> const& stack)
{
    return os<<stack.top()<<'\n';
}

#endif //_STACK1_H_
