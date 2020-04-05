#include <iostream>
#include <memory>
#include <atomic>
#include <thread>
#include <future>

int main()
{
    
    std::shared_ptr<int> ptr=std::make_shared<int>(2011);
    
    for(auto i=0; i<10; ++i) {
        std::thread([i, &ptr]()mutable{
            auto localPtr=std::make_shared<int>(2014+i);
            std::atomic_store(&ptr, localPtr);
            }).detach();
    }
    
    auto f1=std::async(std::launch::async, [&ptr](){
            auto localPtr=std::make_shared<int>(2020);
            std::atomic_store(&ptr, localPtr);
            });
            
      auto f2=std::async(std::launch::async, [&ptr](){
            auto localPtr=std::make_shared<int>(2023);
            std::atomic_store(&ptr, localPtr);
            });
            
    f1.get();
    f2.get();
    
    auto result = std::atomic_load(&ptr);
    
    std::cout<<*ptr<<", atomic load= "<<*result<<'\n';
    return 0;
}
