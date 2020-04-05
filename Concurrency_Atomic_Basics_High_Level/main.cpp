#include <iostream>
#include <atomic>
#include <thread>
#include <future>
#include <chrono>

std::atomic_flag flag = ATOMIC_FLAG_INIT;
 
long data{0};
std::atomic<bool>readyFlag{false};          // always initialize atomic values
                                            // otherwise atomic lock is not initialized

// if default constructor used without initializing the atomic
// it can be locked afterward
//std::atomic<bool>readyFlag; 
//std::atomic_init(&readyFlag, false);        // C style initialization; 

// readyFlag=false                          // valid assignment operation but not atomic initialization
                                            // if not initialized atomic lock will not be initialized
                                            
void provider() {
    // read a character "<return>" to allow some time for threads
    std::cout<<"please enter <return> ";
    std::cin.get();
    
    // write data
    data+=1000;                  // writing operation is atomic and protected by atomic store() function below
    
    
    //readyFlag.store(true, std::memory_order_seq_cst);       // change the value of the atomic<bool> and signal readiness
    readyFlag.store(true, std::memory_order_release);         // store() is a write operation and atomic; note 
    std::cout<<"Provider thread: "<<std::this_thread::get_id()<<'\n'
              <<"data provided: "<<data<<'\n';              // the operations before store is protected almost having a mutexbefore
                                                            // std::memory_order_seq_cst default value if not used; sequential memory order
 //   readyFlag=true;                                       // not atomic; no lock activated
}

void consumer() 
{
    // wait for data to be ready
 //   while(!readyFlag.load(std::memory_order_seq_cst)) {              // the operation below this line is protected as if there is unique_lock
    while(!readyFlag.load(std::memory_order_acquire)) {
        std::cout.put('.').flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    // once the data is ready process the data; this part is protected by the atomic load() above
    std::cout<<"\nConsuming data: "<<data<<'\n'
              <<"Consumer thread:"<<std::this_thread::get_id()<<'\n';
}

int main()
{
    auto p1=std::async(std::launch::async, provider);
    auto c1=std::async(std::launch::async, consumer);
    // check if the atomic type is lock_free 
    
    std::cout<<std::boolalpha<<"is bool lock_free: "<<readyFlag.is_lock_free()<<'\n'; 
    std::cout<<std::boolalpha<<"is bool always lock_free: "<<std::atomic<bool>::is_always_lock_free<<'\n'; 
    assert(std::atomic<bool>().is_lock_free());
    static_assert(std::atomic<bool>::is_always_lock_free);          // compile time check

    return 0;
}
