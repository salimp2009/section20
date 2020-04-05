#include <iostream>
#include <thread>
#include <mutex>
#include <future>
//#include <string>
//#include <string_view>
//#include <chrono>

// std::once_flag and std::call_once() is used for safe initialization in a multithread environment
// once-flag can be called multiple times but will be instantiated only once
// this can be used for singletons in multithread environment..

std::once_flag onceFlag;

void do_once()
{
    std::call_once(onceFlag, [](){
        std::cout<<"Only once....\n";
        std::cout<<std::this_thread::get_id()<<'\n';
        });
}

void do_once2() 
{
    std::call_once(onceFlag, [](){
        std::cout<<"Only once2....\n";
        std::cout<<std::this_thread::get_id()<<'\n';
        });
}

int main()
{
    std::cout<<'\n';
   
    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once2);
    std::thread t4(do_once2);
    std::thread t5(do_once);
    
    do_once();
    do_once2();
    
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    std::cout<<'\n';
    
    return 0;
    
}
