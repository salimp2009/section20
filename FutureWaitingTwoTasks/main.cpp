#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <random>           
#include <exception>

void doSomething(char c)
{
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);
    
    for(std::size_t i{0}; i<10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        std::cout.put(c).flush();
    }
}


int main()
{
    
    std::cout<<"\nStarting 2 operation aysnchornously...\n";
    
    // start two loops asynchoronously to print characters passed
//    std::future<void>f1=std::async([](){ doSomething('.'); });
//    std::future<void>f2=std::async([](){ doSomething('+'); });
    
    auto f1=std::async([](){ doSomething('.'); });        // auto for type deduction; type is void lamda does not return a value
    auto f2=std::async([](){ doSomething('+'); });        // auto for type deduction; type is void lamda does not return a value
    
    // the lambda can capture variable by value or reference; using reference might be risky; 
    // prefer lamda to capture by value if needed
    // If copying is too expensive, ensure that the objects are passed as constant reference
    // and that mutable is not used.
    
    // function objects or class objects can be passed into async also; e.g: 
    // auto a = std::async(&X::mem, x, 42); ...// try to call x.mem(42) asynchronously; 
    // X is a class, small x is an object, x.mem(42) object call class function m with value 42 


    // if at least one of the background tasks is running 
    if( f1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ||
        f2.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ) {
        
        // poll until at least oe of the loops finished
        while( f1.wait_for(std::chrono::seconds(0)) != std::future_status::ready &&
               f2.wait_for(std::chrono::seconds(0)) !=std::future_status::ready ) {
                   
               std::this_thread::yield();       // hint to reschedule to the next thread    
               }                      
        }        
        
        // at least one background operation has finished or none of them was started, 
        // write a newline character and then wait for both loops to end:
       
        std::cout.put('\n').flush();
        
        try {
            // if ready get the results . if not force the tasks to start
            f1.get();
            f2.get(); 
        }
        catch(const std::exception& e)
        {
            std::cout<<"\nEXCEPTION: "<<e.what()<<'\n';
        }
        std::cout<<"\nDone....\n";
        
 return 0;
}