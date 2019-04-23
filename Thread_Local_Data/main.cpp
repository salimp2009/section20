#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Thread_Local Example;
// thread-local storage, is created for each thread separately. 
// It behaves like static data because it’s bound for 
// the lifetime of the thread and is created at its first usage. 
// This means exactly that thread-local variables at namespace scope 
// or as static class members are created before its first use 
// and that thread-local variables declared in a function are created 
// with its first use. 
// Thread-local data belongs exclusively to the thread.

// A static variable is bound to the lifetime of the main thread, 
// a thread_local variable is bound to the lifetime of its thread, 
// a local variable is bound to the lifetime of the scope in which it was created. 


std::mutex coutMutex;

thread_local std::string s{"Hello from "};

void addThreadLocal(const std::string& s2) {
    s+=s2;
    
    //protecting std::cout
    std::lock_guard<std::mutex>lg(coutMutex);
    std::cout<<s<<'\n';
    std::cout<<"\n&s: "<<&s<<'\n';              // the address of s for each thread
    std::cout<<'\n';                            // is different since the thread_local s
                                                // is specific static data to a thread
}

int main()
{
    std::thread t1(addThreadLocal, "t1");
    std::thread t2(addThreadLocal, "t2");
    std::thread t3(addThreadLocal, "t3");
    std::thread t4(addThreadLocal, "t4");
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    std::cout<<"&s: (from main) "<<&s<<'\n';   // thread_local data is even created for the main
                                                
 return 0;
}