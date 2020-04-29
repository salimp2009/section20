#include <iostream>
#include <atomic>
#include <thread>
#include <cstdint>
#include <immintrin.h>

class ReentrantLock
{
private:
    std::atomic<std::size_t>    statusCheck;       // will be used to check to check lock status
    std::int32_t                refCount;
    
public:
    ReentrantLock(): statusCheck{0}, refCount{0} {}
    
    void Acquire() {
      std::hash<std::thread::id> hasher{};
      std::size_t tid=hasher(std::this_thread::get_id());
      while(tid!=statusCheck.load(std::memory_order_relaxed)) {
          
          // spin check until fence/lock is released & keep check
          std::size_t unlockValue{0};
          while(!statusCheck.compare_exchange_weak(unlockValue, tid, std::memory_order_relaxed, 
                                                                     std::memory_order_relaxed)) //acquire fence is below
        {
            // loop until tid matches with current tid so we can fence/lock it
            unlockValue=0;      // set the expected value back to zero because 
                                // compare_exchange sets it to tid of of the holder at that time
            ;                   // may not be need since we already have the expression above
            //PAUSE()          // used on some intel systems in the book but did not work
            _mm_pause();        // intel web site refers to _mm_pause() included in library immintrin.h
                                // and claims it increases performance; need to check on windows
        }
      }
      
      // once we fence/lock it increment the ref_counter so we know we hold and donot cause a deadlock
      // we use the same lock in the body of a already locked section
      ++refCount;  
      
      //all the load operations can not be reordered and will be valid
      std::atomic_thread_fence(std::memory_order_acquire);
    }
    
    void Release() {
       // protect all the store write operations below the fence are valid
       std::atomic_thread_fence(std::memory_order_release); 
       std::hash<std::thread::id> hasher{};
       std::size_t tid=hasher(std::this_thread::get_id());
       std::size_t actual=statusCheck.load(std::memory_order_relaxed);
       // check if own the lock
       assert(actual==tid);
       
       // decrease the counter; release will be done the counter is zero 
       // because the same thread might use the fence/lock
       --refCount;
       if(refCount==0) 
       {
           statusCheck.store(0, std::memory_order_relaxed);  // once we know we dont need the fence/lock release
       }
    }
    
    // a TryAcquire() function can be implemented if needed
};


int main()
{
    // to make sure std::atomic<std::size_t> is lock_free_on current system
    std::atomic<std::size_t> lockfree_check{0};
    std::cout<<std::boolalpha
             <<"lockfree_check: "<<lockfree_check.is_lock_free()<<'\n';     // lock free; so OK to use 
             
   // make an example using Scoped Lock and Reentrant lock 
   // to make sure it works to avoid deadlock

    return 0;
}
