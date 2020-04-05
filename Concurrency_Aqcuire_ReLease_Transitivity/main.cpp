#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::vector<int>SharedWork;
std::atomic<bool>dataProduced{false};
std::atomic<bool>dataConsumed{false};

void dataProducer() {
    SharedWork={1,2,4};
    std::cout<<"producer: data produced...\n";
    dataProduced.store(true, std::memory_order_release);        // synronizes with the deliverBoy()
}

void datadeliverBoy() {
    while(!dataProduced.load(std::memory_order_acquire));       //  wait until the data is ready
    std::cout<<"deliverboy: delivering data...\n";
    dataConsumed.store(true, std::memory_order_release);        // syncronizes with the dataConsumer()
}

void dataConsumer() {
    while(!dataConsumed.load(std::memory_order_acquire));       // wait until the data is delivered
    for(auto& data:SharedWork)
        data*=10;
    std::cout<<"dataConsumer: data is processed...\n";
}

int main()
{
    std::thread t1(dataConsumer);
    std::thread t2(datadeliverBoy); 
    std::thread t3(dataProducer);
    
    t1.join();
    t2.join();
    t3.join();
    
    for(const auto& data:SharedWork)
        std::cout<<data<<'\n';
    std::cout<<'\n';
    
    return 0;
}
