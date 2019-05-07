#include <iostream>
#include <thread>
#include <future>
#include <utility>

// Example to use Promise, Future and Threads
// you can pass promises to function either by reference(&) or rvalue value reference (&&)
// Copy by value is not acceptable for promises & threads; either use std::move() or std::ref()
// if rvalue ref (&&) is used then you have to pass by std::move(promise)
// if lvalue ref(&) is used then use ref wrapper std::ref(promise) when passing promise with a thread

void product(std::promise<int>&& intPromise, int a, int b) {
    intPromise.set_value(a*b);
}

struct Div {
  void operator() (std::promise<int>&& intPromise, int a, int b)  const {
      intPromise.set_value(a/b);
  }
};

int main()
{
    int a{20};
    int b{5};
    
    std::promise<int> prodPromise;
    std::promise<int> divPromise;
    
    std::future<int> fut1=prodPromise.get_future();
    std::future<int> fut2=divPromise.get_future();
    
    Div div;
    
    std::thread t1(product, std::move(prodPromise), a, b);
    std::thread t2(div, std::move(divPromise), a, b);       // the function expects && so use std::move()
    
    std::cout<<'\n';
    std::cout<<a<<" * "<<b<<"= "<<fut1.get()<<'\n';
    std::cout<<a<<"/ "<<b<<"= "<<fut2.get()<<'\n';
    
    t1.join();      // we could use t1.detach() right after the thread creation as an alternative
    t2.join();      // which would allow the thread to work at background and results would be stored in promise
    
    std::cout<<'\n';
    

 
 return 0;
}