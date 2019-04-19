#include <iostream>
#include <atomic>
#include <future>
#include <thread>
#include <chrono>

// ATOMICS EXAMPLE; no mutex or lockguard is neccessary but can be combined
// the order of the operations uses default guarantee
// instead of using mutexes and lock, it might be worth using atomics instead
// if condition_variable is used then we still need the mutex/lock_guard and 
// atomic flags are used for predicates
// For atomic types, you can still use the “useful,” “ordinary” operations, 
// such as assignments, auto- matic conversions to integral types, increments, decrements..etc

long data{0};
std::atomic<bool> readyFlag(false);  // always initialize atomc objects; 
                                     // if not initialize then std::atomic_init(&readyFlag, false)

void provider()
{
    std::cout<<"\n Press enter <return> to provide data"<<'\n';
    std::cin.get();
    
    // provide some data
    data=42;
    
    // signal readiness
    readyFlag.store(true);              // Atomics use .store() to set-change value
}                                       // The store() operation performs a so-called release operation 
                                        // on the affected memory location, which by default ensures 
                                        // that all prior memory operations, whether atomic or not, 
                                        // become visible to other threads before the effect of the store operation.

void consumer()
{
    // check readiness
    while(!readyFlag.load() ){        // atomic .load() aquires the stored value 
        std::cout.put('.').flush();   // while waiting for readiness
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    }
    
    // once ready process data..
    std::cout<<"\nValue: "<<data<<'\n';
}

/* As a consequence, because the setting of data happens 
// before the provider() stores true in the readyFlag and 
// the processing of data happens after the consumer() has loaded true 
// as value of the readyFlag, the processing of data is 
// guaranteed to happen after the data was provided.
// This guarantee is provided because in all atomic operations, 
// we use a default memory order named memory_order_seq_cst, 
// which stands for sequential consistent memory order. 
// With low- level atomics operations, we are able to relax this order guarantee
*/ 

int main()
{
    // start provider and consumer
    auto p1=std::async(std::launch::async, provider);
    auto c1=std::async(std::launch::async, consumer);
    
    // main program runs concurently as well
    std::cout<<"\nMain program is also running.....\n";
 
 return 0;
}

