#include <iostream>
#include <atomic>
#include <thread>
#include <string>

std::atomic<std::string*>ptr{nullptr};
int data{0};
std::atomic<int>atoData{0};

void producer() {
    std::string* p=new std::string("C++11");
    data=2011;
    atoData.store(2017, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    std::cout<<"producer: data ready..\n";
    ptr.store(p, std::memory_order_relaxed);
    
}

void consumer() {
    std::string* p2{nullptr};
    while(!(p2=ptr.load(std::memory_order_relaxed)));
    std::atomic_thread_fence(std::memory_order_acquire);
    std::cout<<"consumer: consuming data..\n";
    std::cout<<"*p2= "<<*p2<<'\n';
    std::cout<<"atoData= "<<atoData.load(std::memory_order_relaxed)<<'\n';
}

int main()
{
    std::cout<<'\n';
    
    std::thread t1(consumer);
    std::thread t3(consumer);
    std::thread t2(producer);
    
    t1.join();
    t3.join();
    t2.join();
    
    
    delete ptr;

    return 0;
}
