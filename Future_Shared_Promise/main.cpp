#include <iostream>
#include <future>
#include <thread>
#include <utility>
#include <cassert>

// Example for std::shared_future
// With shared_future, multiple calls of get() is possible
// therefore different threads can use the data by calling with .get() function
// shared_future is copyable; we can pass it to a function by value However std::future cannot be copied
// a shared future can also be created from a std::future by using fut.share();

std::mutex coutMutex;

struct Div {
    
    void operator()(std::promise<int>&& intPromise, int a, int b) {
        assert(b!=0);
        std::cout<<"\n Division operator Thread ID: "<<std::this_thread::get_id()<<'\n';
        return intPromise.set_value(a/b);
    }
};

struct Requester {
  
    void operator() (std::shared_future<int> sharFut) {
        std::lock_guard<std::mutex>lock(coutMutex);
        int num=sharFut.get();
        std::cout<<"\nDivision Result : "<<num<<" Thread ID: "
                 <<std::this_thread::get_id()<<'\n';
    }
};


int main()
{
    // Create a promise and connect to a shared future
    std::promise<int>divProm;
    std::shared_future<int>shaFut=divProm.get_future();
    
    // Send the promise with a seperate thread to calculate the division
    // and store the result with promise to be called by shared_future within different threads
    Div div;
    std::thread t1(div, std::move(divProm), 20, 10);
    
    // Create seperate threads and requester object to get the result of division
    // by calling thru std::shared_future's get() function
    // the stored result in promise can be accessed thru communication between promise and shared_future
    Requester req;
    std::thread t2(req, shaFut);
    std::thread t3(req, shaFut);
    std::thread t4(req, shaFut);
    std::thread t5(req, shaFut);
    std::thread t6(req, shaFut);
    
    // All child (worker) threads had to be joined to the creater unless they are detached
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    
    std::cout<<'\n';
    
 return 0;
}