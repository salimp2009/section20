#include "Stack1.hpp"
#include <string>
#include <deque>
#include <cassert>
#include <initializer_list>


//..................................................................................................
// Chapter 2.5 Specializations of Class Templates frm Templates Book

// You can specialize a class template for certain template arguments. 
//Similar to the overloading of function templates (see Section 1.5 on page 15), 
// specializing class templates allows you to optimize implementations for certain types 
// or to fix a misbehavior of certain types for an instantiation of the class template.  
// if you specialize a class template, you must also specialize all member  functions.
// Although it is possible to specialize a single member function of a class template, 
// once you have done so, you can no longer specialize the whole class template instance 
// that the specialized member belongs to.
// To specialize a class template, you have to declare the class with a leading template<> 
// and a specification of the types for which the class template is specialized. 
// The types are used as a template argument and must be specified directly following 
// the name of the class:
//..................................................................................................

template<>
class Stack<std::string>
{
private:
    std::deque<std::string>elems;  // elements; original Stack template used vector but it can be changed
    
public:
    Stack() { }
    Stack(std::initializer_list<std::string> l): elems(l) { }
    Stack(std::string& elem): elems{std::move(elem)} { }
    ~Stack() { }
    
    std::deque<std::string> get_deque() const {return elems;}
    void push(std::string const & elem);
    std::string pop();
    std::string const& top() const;
    bool empty() const {
        return elems.empty();
    }

};

Stack(const char*)->Stack<std::string>;


void Stack<std::string>::push(std::string const& elem)
{
    elems.push_back(elem);    
}


std::string Stack<std::string>::pop()
{
    assert(!elems.empty());                // check if the container is empty or not
    std::string last_elem=elems.back();    // make a copy of the last element
    elems.pop_back();                      // remove the last element
    return last_elem;                     // returns a copy of the removed element from top
}

std::string const& Stack<std::string>::top() const
{
    assert(!elems.empty());
    return elems.back();                // returns const reference of the top element
}
