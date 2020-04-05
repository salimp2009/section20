#include <iostream>
#include <atomic>
#include <thread>
#include <functional>
#include <memory>

// Fetch Multiplication Implementation
// it is lock_free but not wait_Free

template<typename T>
T fetch_mult(std::atomic<T>& shared, T mult) {
    T oldValue=shared.load();                                          // return a reference to the atomic value since it is into function by reference
                                                                       // atomic value has to be passed as reference because there is no copy constructor for atomics
    while(!shared.compare_exchange_strong(oldValue, oldValue*mult)) ;  // loop will continue until CAS returns true
                                                                       // which will fail the while loop and changes old value 
    return oldValue;                                                   // with the new value
}


int main()
{
    std::atomic<int> myInt{5};
    std::cout<<"Original value: "<<myInt<<'\n';
    
    fetch_mult(myInt, 25);
    std::cout<<myInt<<'\n';
    
    std::thread t1(fetch_mult<int>, std::ref(myInt), 10);       // need to pass type infor for fethc_mult
    std::thread t2(fetch_mult<int>, std::ref(myInt), 10);       // myInt has to be passed a reference; std::ref() is used for that purpose
    t1.join();
    t2.join();
    
    std::cout<<myInt<<'\n';
    

    return 0;
}
