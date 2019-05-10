#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;  
// this should work 
// as a short cut define seconds by using 0.2s but it did not ; will check w/ windows

void getAnswer(std::promise<int> intPromise) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    intPromise.set_value(42);
}


int main()
{
    std::cout<<'\n';
    
    std::promise<int> answerPromise;
    auto fut=answerPromise.get_future();
    
    std::thread t1(getAnswer, std::move(answerPromise));
    
    std::future_status status{};  // create a future status object to store return value from wait_for()
    do {
        status=fut.wait_for(0.2s);  // using namespace std::literals::chrono_literals for 0.2s;
        std::cout<<"doing something else...\n"; 
        
    } while(status!=std::future_status::ready);
    
    std::cout<<"\nThe answer is: "<<fut.get()<<'\n';
    
    t1.join();
 
 
 return 0;
}