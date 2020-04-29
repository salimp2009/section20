#ifndef _MY_STACK1_H_
#define _MY_STACK1_H_

#include <vector>
#include <cassert>
#include <initializer_list>

template<typename T>
class Stack {
private:
    std::vector<T>elems;
public:
    Stack(T elem);
    
    // Aternative variadic constructor we can use an initializer list
    // use one of them because the constructor will use the first matching constructor and skip the other one 
    // initializer list is better option since custom types can be passed without specifying the types
    // initializer list will deduce the type from Stack template parameter T 
    // if you want to overload then use enable if for initializer list to specify the if the type
    // of args is initializer_list
 //    Stack(std::initializer_list<T>ls):elems{ls} { std::cout<<"initializing with list...\n";}
    
      template<typename... U,
             typename=std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
   Stack(U&& ...args): elems{std::forward<U>(args)...} { std::cout<<"initializing with variadic...\n";}
    
//    template<typename... U,
//             typename=std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
//   Stack(U&& ...args){ 
//                        elems.emplace_back(args...);
//                        std::cout<<"initializing with variadic...\n";}

    
    
    template<typename U>
    void push(U&& elem);
    
    void pop();
    T const& top() const&;
    bool empty() const {
        elems.empty();      // using std::vector empty() member function
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Stack& obj) {
        for(const auto& elem: obj.elems) {
            std::cout<<elem<<" ";
        }
        std::cout<<'\n';
        return os;
    }
};


template<typename T>
Stack<T>::Stack(T elem):elems{std::move(elem)} { }

// if defined outside the class declaration 
template<typename T>
template<typename U>
void Stack<T>::push(U&& elem) {
    elems.emplace_back(std::forward<U>(elem));
}

template<typename T>
void Stack<T>::pop() {
    assert(!elems.empty());     // continue if the container is not empty
    elems.pop_back();
}

template<typename T>
T const& Stack<T>::top() const& {
    assert(!elems.empty());     // continue if the container is not empty
    return elems.back();
}

#endif // _MY_STACK1_H_