#include <iostream>
#include <atomic>
#include <thread>
#include <string>

// Memory_order_consume example;
// compiler implements std::memory_order_consume by using std::memory_order_acquire.
// both programs do the same thing but 
// release-acquire has synchronization between them 
// whereas memory_order_consume uses dependencies on only atomic data  
// therefore if we use memory_order_consume in the following program
// only p2 (in consumer) has a dependency thru ptr.store() & ptr.load() 
// both data (non-atomic) and atoData (atomic) has no dependencies nor sync and 
// We have no guarantee regarding the output of data and atoData

std::atomic<std::string*>ptr;
int data{};
std::atomic<int> atoData;

void producer() {
    std::string* p=new std::string("C++11");
    data=2011;
    atoData.store(2014, std::memory_order_relaxed);
    ptr.store(p, std::memory_order_release);
}

void consumer() {
    std::string *p2{};
//  while(!(p2=ptr.load(std::memory_order_acquire)));         // release-aqcquire memory order
    while(!(p2=ptr.load(std::memory_order_consume)));           // release-consume memory order; not recommended; undefined behaviour
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