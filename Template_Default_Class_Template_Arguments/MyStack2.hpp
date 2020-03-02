#ifndef _MYSTACK2_H_
#define _MYSTACK2_H_

#include <vector>
#include <iostream>

template<typename T, typename Cont=std::vector<T>>
class Stack
{
  friend  std::ostream& operator<<(std::ostream& os, const Stack& obj) {
        for(const auto& elem:obj.elems)
            os<<elem<<" ";
        return os;
    }
private:
    Cont elems;
public:
    Stack()=default;
    Stack(T n): elems{std::move(n)} { }
    
    template<typename...U>
    Stack(U&&...args): elems{std::forward<U>(args)...} { }
    
    template<typename U>
    void push(U&& elem);
    void pop();
    const T& top() const;
    bool empty() const {
        return elems.empty();
    }
};
 template<typename T, typename Cont>
 template<typename U>
 void Stack<T, Cont>::push(U&& elem) {
     elems.emplace_back(std::forward<U>(elem));
 }

//template<typename T, typename Cont>
//void Stack<T, Cont>::push(const T& elem) {
//    elems.push_back(elem);
//}

template<typename T, typename Cont>
void Stack<T, Cont>::pop() {
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T, typename Cont>
const T& Stack<T, Cont>::top() const {
    assert(!elems.empty());
    return elems.back();
}

#endif // _MYSTACK2_H_