#include <iostream>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <random>           
#include <exception>


int querrynumber()
{
    //read number
    std::cout<<"Enter the number of characters to print: ";
    int num;
    std::cin>>num;
    
    if(!(std::cin)) throw std::runtime_error("no number read");
    return num;
}

void doSomething(char c, std::shared_future<int>f)
{
    try {
        // wait for the number characters to print
        int num=f.get();    // num will be provide by shared future f
        
        for(size_t i{0}; i<num; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout.put(c).flush();
        }
    }
    catch(const std::exception& e) 
    {
        std::cerr<<"Exception in thread: "<<std::this_thread::get_id()
                 <<" "<<e.what()<<'\n';
    } 
}

int main()
{
   try { 
        
        // get the number of characters 
        // and pass it with a shared future so other threads can use the same number
        std::shared_future<int>f=std::async(querrynumber);  // pass only the function name; 
                                                            // e.g. no need for func() only func,
                                                            
        // Alternative way of creating a shared future from an ordinary future  
//      auto f=std::async(querrynumber).share();                                                 
        
        // start 3 threads each printing their characters with the same number in the function(doSomething)
        auto f1=std::async(std::launch::async, doSomething, '+', f);  // function takes two parameters
        auto f2=std::async(std::launch::async, doSomething, '.', f);
        auto f3=std::async(std::launch::async, doSomething, '*', f);
        
        //wait for all loops to be finished
        f1.get();
        f2.get();
        f3.get();
   }
    catch(const std::exception& e)
    {
        std::cerr<<"Exception error: "<<e.what()<<'\n';
    }
    
    std::cout<<"\nFinishing Program......\n";
    
 return 0;
}