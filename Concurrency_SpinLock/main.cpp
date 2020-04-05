#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class Spinlock
{
std::atomic_flag flag=ATOMIC_FLAG_INIT;     // atomic_flag is always_lock_free boolean and 
                                            // and can only be initialized this way; no store(), load() functions
                                            // it is initialized to False
public: 


constexpr void lock() {                                       
    while(flag.test_and_set(std::memory_order_acquire) )                    // atomically checks and sets the current value; 
           ; // this will make sure the while loop runs until locked       // if false, it wil be set true and return the od value
} 

void release() {
    flag.clear(std::memory_order_release);                           // atomically sets the flag value to false
}

};

Spinlock spin;
std::size_t counter{0};

void workonResource(int n) {
    for(int i{0}; i<100; ++i) {
        spin.lock();            // check the flag until it is locked
        std::cout<<"Output from thread "<<n<<'\n';
        ++counter;
        spin.release();         // unlock so next thread can have chance but current thread will
                                // be in for loop until it is done in this example; it will print 100 times
    }
}

int main()
{
    std::vector<std::thread> v ;
    constexpr int n{10};
    for(int i{0}; i<n; ++i) {
        v.emplace_back(workonResource, i);
    }

    for(auto& thread:v)
        thread.join();
     
    // total number will 
    std::cout<<"Total lines printed: "<<counter<<'\n';
        
    return 0;
}
