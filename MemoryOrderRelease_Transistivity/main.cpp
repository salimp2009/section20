#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

// Memory order: Acquire-Release Semantic
// The acquire-release semantic is transitive 
// That means if we have an acquire-release semantic between two threads (a, b) 
// and an acquire-release semantic between (b, c), 
// then there is an acquire-release semantic between (a, c)

std::vector<int> mySharedWork;
std::atomic<bool> dataProduced{false};
std::atomic<bool> dataConsumed{false};

void dataProducer() {
    mySharedWork={1,0,5};
    dataProduced.store(true, std::memory_order_release);
    std::cout<<"\nProducer: "<<std::this_thread::get_id()<<'\n';
}

void deliveryBoy() {
    while(!dataProduced.load(std::memory_order_acquire));
    dataConsumed.store(true, std::memory_order_release);
    std::cout<<"\nDelivery: "<<std::this_thread::get_id()<<'\n';
}

void dataConsumer() {
    while(!dataConsumed.load(std::memory_order_acquire));
    mySharedWork[2]=3;  
     std::cout<<"\nConsumer: "<<std::this_thread::get_id()<<'\n';
}



int main()
{    
    std::thread c1(dataConsumer);
    std::thread d1(deliveryBoy);
    std::thread p1(dataProducer);
    
    std::cout<<"\nMain program is also running..\n"<<std::this_thread::get_id()<<'\n';
    
    c1.join();
    d1.join();
    p1.join();
    
    for(const auto v: mySharedWork)
        std::cout<<v<<" ";
    std::cout<<'\n';
    
    return 0;
}


