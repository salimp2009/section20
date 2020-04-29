#include <iostream>
#include <future>
#include <thread>
#include <utility>

void product(std::promise<int>&& intPromise, int a, int b) {
    intPromise.set_value(a*b);
}

struct Div 
{
  void operator()(std::promise<int>&& intPromise, int a, int b) const {
      intPromise.set_value(a/b);
  }
};


int main()
{
    int a{20}, b{10}; 
    
    std::promise<int>prodPromise;
    std::promise<int>divPromise;

    std::future<int> prodFut=prodPromise.get_future();
    std::future<int> divFut=divPromise.get_future();

    std::thread prodThread(product, std::move(prodPromise), a, b);
   // Div div;
    std::thread divThread(Div(), std::move(divPromise), a, b);
    
    std::cout<<"Product result: "<<prodFut.get()<<'\n';
    std::cout<<"Product result: "<<divFut.get()<<'\n';
    
    prodThread.join();
    divThread.join();
    
    return 0;
}
