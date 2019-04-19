#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <exception>
#include <stdexcept>
#include <utility>
#include <functional>

// function expects a promise object by reference
void doSomething(std::promise<std::string>& p)               
{
    try{
        std::cout<<"\nRead char ('x' for exception): ";
        char c = std::cin.get();
        if(c=='x') {
            throw std::runtime_error(std::string("char ")+c+" read");
        }
        
        std::cout<<"\nActive thread: "<<std::this_thread::get_id()<<'\n';
        std::string s = std::string("char ")+c+" processed";
        p.set_value(std::move(s));                    // store result in promise object; p.set_value()
//      p.set_value_at_thread_exit(std::move(s));     // if we want to wait until thread is done
    }catch(...) {
        p.set_exception(std::current_exception());    // store exception in promise object; o.set_exception()
//        p.set_exception_at_thread_exit(std::current_exception());  // if we want to wait until thread is finished
    }

}

int main()
{
    try{
        std::promise<std::string>p;
        std::thread t(doSomething, std::ref(p));  // by using std::ref(p), we are creating a reference to p 
        t.detach();                               // we can pass several promises into the same thread 
                                                  // to store other information
                                                  // promise object cannot be  copied or passed by value
                                                  
        // create a future to process the outcome from promise object
        // promise object will store the result of thread that is detached
        // in order to get that result and use it we need a future object that will have the
        // result stored in the assigned promise
        std::future<std::string>f(p.get_future());
        
        // process the outcome
        std::cout<<"\nResult: "<<f.get()<<'\n';
        
        //Note that get() blocks until the shared state is ready, 
        //which is exactly the case when set_value() or 
        //set_exception() was performed for the promise. 
        //It does not mean that the thread setting the promise has ended. 
        //The thread might still perform other statements, 
        //such as even store additional outcomes into other promises.
        
    } catch(const std::exception& e) {
        std::cerr<<"\nEXCEPTION: "<<e.what()<<'\n';
    } catch(...) {
        std::cerr<<"\nError: \n";
    }
    
 return 0;
}