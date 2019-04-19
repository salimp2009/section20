#include <iostream>
#include <atomic>
#include <thread>
#include <string>

// Acquire-Release-Fences;
// Fences guarantees the order of the operation will not be changed; either by CPU or compiler
// atomic_thread_fence; acquire guarantees the write/store  operation
// after the fence can not happen before; load-store or store-store o

// atomic_thread_fence;release guarantees the read/load operation before 
// the fence can not happen after; load - load or load - store

// most apparent difference between acquire and release fences and atomics 
// with acquire-release semantics is that fences need no atomics. 
// There is also a more subtle difference; the acquire and release fences are 
// more heavyweight than the corresponding atomics.

std::atomic<std::string*>ptr;
int data{};
std::atomic<int> atoData;



void producer() {
    std::string* p=new std::string("C++11");
    data=2011;
    atoData.store(2014, std::memory_order_relaxed);             // relaxed can be used because of the fence
    std::atomic_thread_fence(std::memory_order_release);        // guarantees the store operation after cannot happen before
    ptr.store(p, std::memory_order_relaxed);                    // relaxed can be used because of the fence
}

void consumer() {
    std::string *p2{};
    while(!(p2=ptr.load(std::memory_order_relaxed)));           // relaxed can be used because of the fence
    std::atomic_thread_fence(std::memory_order_acquire);        // guarantees the load operation before cannot happen after
    std::cout<<"\n*p2= "<<*p2<<'\n';
    std::cout<<"\ndata= "<<data<<'\n';
    std::cout<<"\natoData= "<<atoData.load(std::memory_order_relaxed)<<'\n';
}

int main()
{
    std::thread c1(consumer);
    std::thread p1(producer);
    
  //  std::cout<<"\nMain program is working..\n";
    
    c1.join();
    p1.join();
    
    std::cout<<"\nFinishing program...\n";
    
    std::cout<<'\n';

 return 0;
}