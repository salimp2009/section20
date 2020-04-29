#include <iostream>
#include <atomic>
#include <thread>
#include <type_traits>
#include <functional>
#include <string>
#include <immintrin.h>


class Spinlock 
{
    std::atomic_flag lockFlag=ATOMIC_FLAG_INIT; // ATOMIC_FLAG_INIT is a macro and returns {false}
public:
    Spinlock()=default;
    
    void Acquire() {
        while(lockFlag.test_and_set(std::memory_order_acquire))
        {
            _mm_pause();  // PAUSE() is used in book but intel compiler refers to this in spinlocks
                          // in header immintrin.h // to checked on Windows systems!!
        }
    }
    
    void Release() {
        lockFlag.clear(std::memory_order_release);
    }
};

template<typename LOCK>
class ScopedLock 
{
  typedef LOCK lock_t;
  lock_t* m_lock;
public:
  explicit ScopedLock(lock_t& lock): m_lock{&lock} 
  {
      m_lock->Acquire();
  }
  
  ~ScopedLock() 
  {
      m_lock->Release();
  } 
};

int threadSafeFunction(Spinlock& lock) {
    ScopedLock<std::decay_t<decltype(lock)>>janitor{lock};
    std::cout<<"Doing some work: "<<std::this_thread::get_id()<<'\n';
    return 1;           //lock will be released at the exit
}


int main()
{
    Spinlock spinlock{};
    std::thread t1(threadSafeFunction, std::ref(spinlock));
    std::thread t2(threadSafeFunction, std::ref(spinlock));
    std::thread t3(threadSafeFunction, std::ref(spinlock));
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}
