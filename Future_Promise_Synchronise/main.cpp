#include <iostream>
#include <future>
#include <thread>

// Example Using set_value and wait() functions of Future and Promise
// to provide synchorinsation between thread  using shared data
// future will wait until the promise sets the value; 
// therefore set_value()and wait() will provide synchronisation between threads

// Although this is synchronized, the data is not protected to use multiple threads
// for reading or writing threads;

void doTheWork() {
    std::cout<<"\nProcessing shared data.."<<std::this_thread::get_id()<<'\n';
}

void waitingForWork(std::future<void>&& fut) {
    std::cout<<"\nWorker: Waiting for work...\n";
    fut.wait();
    doTheWork();
    std::cout<<"\nWork Done..Thread ID::"<<std::this_thread::get_id();
}

void setDataReady(std::promise<void>&& prom) {
    std::cout<<"\nData is ready..."<<std::this_thread::get_id()<<'\n';
    prom.set_value();
}

int main()
{
    std::cout<<'\n';
    
    std::promise<void>prom;
    std::future<void>fut=prom.get_future();
    
    std::thread t1(waitingForWork, std::move(fut));
    std::thread t2(setDataReady, std::move(prom));
    
    t1.join();
    t2.join();
    
    std::cout<<'\n';
    

 
 return 0;
}