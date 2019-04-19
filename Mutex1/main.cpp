#include <iostream>
#include <future>
#include <mutex>
#include <string>

// MUTEX AND LOCKS
// A mutex, or mutual exclusion, is an object that helps to control 
// the concurrent access of a resource by providing exclusive access to it.
// The resource might be an object or a combination of multiple objects. 
// To get exclusive access to the resource, the corresponding thread locks the mutex, 
// which prevents other threads from locking that mutex 
// until the first thread unlocks the mutex.


// create a Mutex for print function access; (it can be an object; function, variable..etc)
std::mutex printMutex;

void print(const std::string& s)
{
    std::lock_guard<std::mutex>lg(printMutex);     // lock_guard<std::mutex> puts an automatic lock/unlock
    for (const auto& c:s) {                        // guard so that active thread locks it but if there is an
       std::cout.put(c);                           // exception thrown before it is unlocked lock_guard 
    }                                             // unlocks it. Lock_guard lifetime should be short because
    std::cout<<'\n';                              // it blocks the other threads and functions
}                                                 // if it is in main put it in between {    }

int main()
{
    std::future<void> f1=std::async(std::launch::async, 
                                     print,"Salim from future1");
    
    std::future<void> f2=std::async(std::launch::async,
                                    print, "Sema is from future2");
                                    
        print("Hello from main from program....");

 return 0;
}