#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Example for Showing Thread Local, local data and lifetime of scope

// A static variable; is bound to the lifetime of the main thread, 
// a thread_local variable; is bound to the lifetime of its thread, 
// a local variable; is bound to the lifetime of the scope in which it was created. 



std::mutex coutMutex;
thread_local std::string s{"Hello from"};

void first() {
    s+="first";
}

void second() {
    s+="second";
}

void third() {
    s+="third";
}

void threadLocalState(std::string const& s2) {
    s+=s2;
    
    first();
    second();
    third();
    
    std::lock_guard<std::mutex>lg(coutMutex);
    std::cout<<s<<'\n';
    std::cout<<"\n&s: "<<&s
            <<" thread id: "<<std::this_thread::get_id()<<'\n';
    std::cout<<'\n';
}


int main()
{
    std::cout<<'\n';
    
    std::thread t1(threadLocalState, "t1: ");
    std::thread t2(threadLocalState, "t2: ");
    std::thread t3(threadLocalState, "t3: ");
    std::thread t4(threadLocalState, "t4: ");
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    std::cout<<"\nFinishing program...\n";
    std::cout<<'\n';
   
 return 0;
}