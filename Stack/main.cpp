#include <iostream>
#include <stack>
#include <vector>
#include <list>

// Stack Example;
// Stack is LIFO data structure; Last-in-First-Out
// Stack donot support iterators; 
// the default container type std::deque

template<typename T>
void display(std::stack<T> s) {                 // the display function displays the elements of stack
    std::cout<<"\n[";                          // using repeadetly the top() and pop() functions
    while(!s.empty()) {                           // the original stack is not affected since it is a copy
        std::cout<<s.top()<<" ";                        
        s.pop();                         
    }
    std::cout<<"]\n";
}

int main()
{
    std::stack<int>s;                       // default container in stack is std::deque<>
    std::stack<int, std::vector<int>>s1;    // the container type can be specified; container needs to support push_back
    std::stack <int, std::list<int>>s2;     // back(), pop_back() operations
    
    for(int i:{1,2,3,4,5})                    // range base for loop with an initializer list
        s.push(i);
    display(s);
    
    s.push(100);
    display(s);
    
    s.pop();
    s.pop();
    display(s);
    
    while(!s.empty())
        s.pop();
    display(s);
    
    std::cout<<"\nSize: "<<s.size()<<'\n';
    
    s.push(10);
    display(s);
    
    s.top()=100;            // top() returns a reference; therefore assigning 
    display(s);             // a new value changes the existing value of the top element
    
    return 0;
}