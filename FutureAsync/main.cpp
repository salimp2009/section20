#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <random>           
#include <exception>

// Futures & Multithreading

int doSomething(const char c)
{
    // random number generator using 'c' as a seed
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10,1000);    // Produces random integer values i, uniformly distributed 
                                                       //on the closed interval [a, b], that is, distributed according to the discrete probability function

    // this thread will sleep for random amount of time and print 'c' 10 times afterwards
    for(std::size_t i=0; i<=10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        std::cout.put(c).flush();
    }    
    return c;
}


int func1()
{
    return doSomething('.');
}

int func2()
{
    return doSomething('+');
}

int main()
{
    std::cout<<"\nStarting func1() in the back ground"
             <<" and func2() in foreground:\n";
    
    // start func1 asynchornously (now or later)
    // std::future<int>result1(std::async(func1));   // starting func1 using std::async(), 
                                                    // and assign the result to an object of class std::future:
    
    
    std::future<int>result1(std::async(std::launch::async, func1)); // std::launch forces func1 to start now
                                                                      // If the asynchronous call fails(low resources...etc)  
                                                                      // the program will throw a std::system_error exception
                                                                      
    int result2 = func2();                       // calling func2() syncronously here and now
    
    // wait for func1 to finish and add to result2
    int result=result1.get()+ result2;          // if func1() was started but has not finished yet, 
                                                // get() blocks and waits for its end and yields the result
                                                // if func1 has not started then get() will start it 
                                                // and will block the result unti it finished
    
    
    // To have the best effect, in general, your goal should be to maximize the distance between calling async() and calling get(). 
    // Call early and return late.
    
    // int result=result2 + result1.get();      // Not efficient for multithreading since result1 might start after result2 
    
    
    // the object passed to async() may be any type of a callable object: 
    // function, member function, function object, or lambda 
    // you can also pass the functionality that should run in its own thread inline as a lambda
    
    //Exceptions & throw; get() for futures also handles exceptions.
    
    std::cout<<"\nresult of func1()+func2(): "<<result<<'\n';

 return 0;
}