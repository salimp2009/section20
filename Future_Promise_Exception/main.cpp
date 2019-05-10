#include <iostream>
#include <thread>
#include <future>
#include <utility>

// Example for Exception catching using Promise and Future
// Promise object will store either the result or the exception
// When future calls for the result, it has to deal with the result or the excetion

// the std::promise is destroyed without calling the set-method or 
// a std::packaged_task before invoking it, a std::future_error exception 
// with an error code std::future_errc::broken_promise would be stored in the shared state.

struct Div {
    
    void operator()(std::promise<int>&& intPromise, int a, int b) {
    try {
        // if the denominator is zero, the division is undefined, throw an exception
        if(b==0) {
            std::string errMess=std::string("Illegal division by zero: ")+
                                std::to_string(a)+"/"+std::to_string(b);
           throw std::runtime_error(errMess);                     
        }
        
        // if there is no problem store the result
        intPromise.set_value(a/b);
    
    // Promise has to catch and store the exception to be handled by the future
    } catch(...) {
        intPromise.set_exception(std::current_exception());
    }
    }
    
   
    
};

void executeDivision(int nom, int denom) {
    std::promise<int>intPromise;
    std::future<int>fut=intPromise.get_future();
    
    Div div;
  
    std::thread t1(div, std::move(intPromise), nom, denom);
   
   // Future has to deal with the result or exception stored in promise
   try { 
        std::cout<<nom<<" / "<<denom<<" = "<<fut.get()<<'\n';
   
   } catch(std::runtime_error& e) {
       std::cerr<<"\nError: "<<e.what()<<'\n';
   } catch(...) {
       std::cerr<<"\nError..\n";
   }
   
   t1.join();
}

int main()
{
    std::cout<<'\n';
    
    // the first execution will throw exception and will be handled in the function
    // therefore the main will continue to run and the second call will be executed
    
    executeDivision(20,0);
    executeDivision(20,10);
    
    std::cout<<'\n';
 
 return 0;
}