#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

// Atomic_Flag and Spinlock Example

/* A spinlock is an elementary lock such as a mutex. 
// In contrast to a mutex, it waits not until it gets its lock. 
// It eagerly asks for the lock to get access to the critical section.
// It saves the expensive context switch in the wait state 
// from the user space to the kernel space, but it entirely utilises 
// the CPU and wastes CPU cycles. 
// If threads are typically blocked for a short time period, 
// spinlocks are quite efficient. 
// Often a lock uses a combination of a spinlock and a mutex. 
// The lock first uses the spinlock for a limited time period.
//  If this does not succeed the thread is then be put in the wait state.
*/

class Spinlock {
   std::atomic_flag flag = ATOMIC_FLAG_INIT;   // std::atomic_flag is set to false and is the only lock-free atmoic boolean 
                                               // atomic_flag can be only be initialize with ATOMIC_FLAG_INIT macro;
                                               // initialized to FALSE by ATOMIC_FLAG_INIT macro
public:
   void lock() {
       while (flag.test_and_set() );         // .test_and_set() checks and sets the atomic_flag to TRUE state
   }                                         // this is similar to mutex.lock() 
                                            // which is used to protect a critical section
                                            // The method test_and_set consists of two operations: reading and writing
                                            // it reads first; if the atomic_flag is FALSE then it sets it to TRUE 
                                            // otherwise waits but constantly checks; aggresive
                                            // .clear() sets the atomic_flags to FALSE state
                                            // similar to mutex.unlock()
  void unlock() {                          
       flag.clear();                        
   }                                        
};

Spinlock spin;

void workonResource() {
    spin.lock();                                             // lock the critical section
    // shared resource
    std::cout<<"\nThread ID: "<<std::this_thread::get_id();  // do critical operations
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // just to experiment 
    spin.unlock();                                           // unlock so other threads can use it   
}

int main()
{
    std::thread t1(workonResource);
    std::thread t2(workonResource);
    
    std::cout<<"\nMain thread is also working...\n";
    
    t1.join();
    t2.join();
    
     std::cout<<"\nProgram finished...\n";

 return 0;
}