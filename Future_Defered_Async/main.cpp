#include <iostream>
#include <future>
#include <chrono>

int main()
{
    std::cout<<'\n';
    
    auto begin=std::chrono::system_clock::now();
    
    
    auto lazysync = std::async(std::launch::deferred, 
                                []() {return std::chrono::system_clock::now();});
                                
    auto eagersync=std::async(std::launch::async, 
                                [](){return std::chrono::system_clock::now();});
                                
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    auto lazystart= lazysync.get()-begin;
    auto eagerstart=eagersync.get()-begin;
    
    auto lazyduration=std::chrono::duration<double>(lazystart).count();
    auto eagerduration=std::chrono::duration<double>(eagerstart).count();
    
    std::cout<<"\nLazy Start Duration: "<<lazyduration<<'\n';
    std::cout<<"\nEager Start Duration: "<<eagerduration<<'\n';
    
    std::cout<<'\n';

 return 0;
}