#include <iostream>
#include <atomic>
#include <thread>

// Spinlock example with memory_order_release & acquire; 
// the standart memory order in atmoics is sequential std::memory_order_seq_cst
// but release and acquire is more relaxed; 
// the order of threads is not set but the atomic values guarantee the modification order
// this memory order is safer than relaxed version where there is no guarantee at all

class Spinlock {
  std::atomic_flag flag=ATOMIC_FLAG_INIT;            // lock free atomic flag
public:
    Spinlock()=default;                             // atomic_flag can only be initialized with
    ~Spinlock()=default;                            // ATOMIC_FLAG_INIT
    void lock() {
        while(flag.test_and_set(std::memory_order_acquire));
    }
    
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

Spinlock spin;

void workonResource() 
{
    spin.lock();
    std::cout<<"\nWorking on resource: "<<std::this_thread::get_id()<<'\n';
    spin.unlock();
}


int main()
{
        std::thread t1(workonResource);
        std::thread t2(workonResource);
        
        std::cout<<"\nMain program is also working..\n";
        
        t1.join();
        t2.join();
        
        std::cout<<"\nFinishing program...\n";
 
 return 0;
}