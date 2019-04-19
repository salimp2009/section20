#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

// Thread example with Shared Data
// All global stream objects (std::cout, std::cin, std::cerr, and std::clog) is thread-safe.
// writing to std::cout is not a data race but a race condition. 
// This means that the output depends on the interleaving of threads.

std::mutex coutMutex;

class Worker {
private:
    std::string name;
public:
    Worker(std::string name): name{std::move(name)} { }
    void operator()() {
        for(std::size_t i{0}; i<=3; ++i) {
            // begin work
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            // end work
            {
                coutMutex.lock();                                   // if no mutexes used; there will be a race condition at cout
                std::cout<<name<<": Work "<<i<<" done!!!\n";        // cout is thread safe so no data race but without locks there will be race condition
                coutMutex.unlock();                                 // the problem here is if there is an exception
            }                                                       // thrown between the lock and unlock there will be a deadlock
        }                                                           // other threads cannot proceed and the mutex willnot be unlocked
    }                                                               // it is safer to use std::lock_guard<std::mutex>lock(coutMutex)
};                                                                  // lock_guard ensures to unlock if there is an exceptipn thrown
    

int main()
{
    std::cout<<'\n';
    
    std::cout<<"\nBoss:let us start working...\n";
    std::thread t1(Worker{"Herb"});
    std::thread t2(Worker{"  Andrei"});
    std::thread t3(Worker{"   Scott"});
    std::thread t4(Worker{"    Bjarne"});
    std::thread t5(Worker{"     Bart"});
    std::thread t6(Worker{"      Jenne"});
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    
    std::cout<<'\n';
    
 return 0;
}