#include <iostream>
#include <atomic>
#include <thread>
#include <string>

std::atomic<std::string*>ptr;
int data{0};
std::atomic<int>atoData{0};


void producer() {
    std::string* p=new std::string("C++11");
    data=2011;
    atoData.store(2014, std::memory_order_relaxed);
    ptr.store(p, std::memory_order_release);
}

void consumer() {
    std::string* p2{nullptr};
//    while(!(p2=ptr.load(std::memory_order_acquire)));
    while(!(p2=ptr.load(std::memory_order_consume)));                          // although memory_order_consume is similar to acquire; it is not recommended
    std::cout<<"*p2= "<<*p2<<'\n';                                            // because consume is not synorized with store but does not protect what comes after
    std::cout<<"data: "<<data<<'\n';                                          // therefore any line below consume is not protected in this case 
    std::cout<<"atoData= "<<atoData.load(std::memory_order_relaxed)<<'\n';    // however acquire has both syncronization and also protects the line below
}

int main()
{
    std::thread t1(consumer);
    std::thread t2(producer);
    
    t1.join();
    t2.join();

    return 0;
}
