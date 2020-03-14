#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <exception>
#include <random>
#include <string>

std::string time() {
    static auto start=std::chrono::steady_clock::now();
    std::chrono::duration<double>d=std::chrono::steady_clock::now()-start;
    return "[" + std::to_string(d.count())+"s]";
}


int doSomething(char c) {
    //  'c' is used as a seed to random engine
    // mt19937 is a random number generating algorithm
    // included in STL better than std::default_random_engine
    std::mt19937 gen(c);
    // use a uniform distribution engine so the random number
    // generator will create a number in between these two values
    std::uniform_int_distribution<int>id(10, 1000);
    
    for(int i{0}; i<10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(id(gen)));
        std::cout.put(c).flush();
    }
    return c;
}

int func1() {
    return doSomething('.');
}

int func2() {
    return doSomething('+');
}

class X {
  public:
    void mem(int num) {std::cout<<"Class X data: "<<num+45<<'\n';}
    
};

int main()
{
    std::cout<<time()<<"launching thread\n";
    
    std::cout<<"starting func1() in background "
             <<"and func2() in the main-foreground..\n";
    
    /* create a future so that and pass the function to a thread
    // the type of the future should match  type of the final return
    // if you have doubt about the return type use auto
     */ 
    //std::future<int>fut1{std::async(func1)};
    
   
    // std::launch::async ; agressive start of async; starts the thread right away
    std::future<int>fut1{std::async(std::launch::async, func1)};  
    
    
    
    /* passing variable to threads thru lambdas or any function should be by copy
    // if passed by reference the lifetime of the passed object may be shorter than the
    // function therefore it is risky; if the background function(doSomething) expect the variable
    // by reference than it is OK since the lifetime of the object is extended until the background task finishes
    // but if you pass the same object to another thread then data race might occur if there is no syncronization
    */ 
    
    char c{'x'};
    std::future<int>fut2{std::async(std::launch::async, [=](){ return doSomething(c);})};
    
    // example for passing a class member function, an object of that class, data to function
    X xx;
    auto fut3=std::async(std::launch::async, &X::mem, xx, 250);
    
    
    //std::launch::deferred; thread start waits the get() call
    //std::future<int>fut1{std::async(std::launch::deferred,func1)};
    
    /* calling second function to start in main while the first function
    // will be run on a seperate thread (if possible; determined by the operating system)
    // the order of the functions change from system to system and also the time
    // it is running depending availibity of the cores
     */ 
    int result2=func2();
    
    /* get() function will call the future and get the stored result
    // if the result is ready it will be executed if not it will wait until
    // background thread fut1 finishes the execution
    */
    
    // wait(), wait_for(), wait_until() are functions to hold the the future
    // wait() functions also return the status of the future which can be used
   
    std::cout<<'\n'<<time()<<": total time before wait\n";
    fut1.wait_for(std::chrono::seconds(3));
    fut1.wait_until(std::chrono::steady_clock::now()+std::chrono::seconds(2));
    std::cout<<'\n'<<time()<<": total time after wait\n";
   
    /* check first if the status is not deferred otherwise the inner while loop
    // that checks the status may go into endless loop because if the deferred method
    // is selected or if run on a single core then the status will not be ready
    // until get() function is called
    */ 
    if(fut1.wait_for(std::chrono::seconds(0))!=std::future_status::deferred) {
        std::cout<<"future thread is active but not ready yet...\n";
        while(fut1.wait_for(std::chrono::seconds(0))!=std::future_status::ready) {
            std::cout<<"future thread is not ready yet...\n";
            std::this_thread::yield();
        }
    }
   
    // get() can be called only once; after the get function the future becomes
    // in an invalid state
    int result=fut1.get()+fut2.get()+result2;
    std::cout<<"state of future after get: "<<std::boolalpha<<fut1.valid()<<'\n';  // checking the state of future after get()
    std::cout<<'\n'<<time()<<": total time thread worked\n";
    std::cout<<"\nresult: "<<result<<'\n';
    
    

    return 0;
}
