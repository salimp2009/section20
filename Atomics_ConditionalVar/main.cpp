#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>

// Atomic<bool> with Conditional Variable
// The downside of the various variations of std::atomic is that you do not have 
// the guarantee that they are lock-free.
// check with .is_lock_free(); return true if no internal lock is used

std::vector<int>mySharedWork;
std::atomic<bool> dataReady(false);

void WaitingforWork() {
    std::cout<<"\nWaiting for work...\n";
    while(!dataReady.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    mySharedWork.at(1)=5;
    std::cout<<"\nMyShared Work Done...\n"
             <<"\nThread ID: "<<std::this_thread::get_id()<<'\n';
}

void setdataReady() {
    // make data ready
    mySharedWork={1,0,3};
    
    // notify the data is ready
    dataReady.store(true);
    // dataReady=true;
    std::cout<<"\nData Ready......"
             <<"\nThread ID: "<<std::this_thread::get_id()<<'\n';
}


int main()
{
    std::cout<<'\n';
    
    std::thread c1(WaitingforWork);
    std::thread p1(setdataReady);
    
    c1.join();
    p1.join();
    
    for(const auto& v: mySharedWork)
        std::cout<<v<<" ";
    
    std::cout<<"\nFinishing program...\n";
    std::cout<<dataReady.is_lock_free()<<'\n';  //true if the system does not internally use locks

 return 0;
}

/* The atomic type std::atomic<user-defined type> supports 
// the same interface as std::atomic<bool>.
// Here are the restrictions for a user-defined type to become an atomic type:
    //• The copy assignment operator for user-defined type, 
    // for all base classes of the user-defined type and 
    // all non-static members of the user-defined type, must be trivial.
    // This means that you must not define the copy assignment operator, 
    // but you can request it from the compiler by using default
    // • a user-defined type must not have virtual methods or 
    // virtual base classes
    // • auser-defined type must be bitwise comparable so that 
    // the C functions memcpy or memcmp can be applied
    // Most popular platforms can use atomic operations for 
    // std::atomic<user-defined type> if the size
    // of the user-defined type is not bigger as the size of an int.
    */
    
    /* Check type properties at compile time;
    // The type properties on a user-defined type can be checked at 
    // compile time, by using the following functions: 
    // std::is_trivially_copy_constructible, std::is_polymorphic and 
    // std::is_trivial. All these functions are part of the very 
    // powerful type-traits library.
    */