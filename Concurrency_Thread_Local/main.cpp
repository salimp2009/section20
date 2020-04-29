#include <iostream>
#include <thread>
#include <string>
#include <mutex>

std::mutex coutMutex;
thread_local std::string s("hello from ");


void addThreadLocal(const std::string& s2)
{
    s+=s2;                              // s is local to each thread and every thread has their own copy of s2
    std::lock_guard guard(coutMutex);   // lock is used to protect cout  
    std::cout<<s<<'\n';
    std::cout<<"address of each &s is unique to thread: "<<&s<<'\n';
}   // lock is released here

int main() 
{
    std::cout<<'\n';
    
    std::thread t1(addThreadLocal, "t1");
    std::thread t2(addThreadLocal, "t2");
    std::thread t3(addThreadLocal, "t3");
    std::thread t4(addThreadLocal, "t4");
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    return 0;
}
