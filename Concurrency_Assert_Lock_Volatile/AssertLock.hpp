#ifndef _ASSERT_LOCK_H
#define _ASSERT_LOCK_H



class AssertLock
{
  // volatile is NOT ATOMIC but it will let us to detect if there were any attemps 
  // tif there are any overlaps between two critical sections if not then we dont need to lock
  // but if there is one thread will change the lock and when the other thread tries before it is released
  // assert will throw an error and programmer can determine which sections should be locked
  // However to get a 90% correctness rate we need to get a big team of developers(100+) run it 
  // multiple times during the day
  
  volatile bool     m_locked;

public:
    AssertLock():m_locked{false} {}
    
    void Acquire() {
        // check if no has the lock
        assert(!m_locked);
        
        // now we can lock
        m_locked=true;
    }
    
    void Release() {
        // Release should be called after Acquire because 
        // if it is never locked then Release will fail too
        // if we try to release without Acquire we may also Release another threads lock
        // which will cause a data race;

        assert(m_locked);
        
        // unlock
        m_locked=false;
        }
    };
    
    #if ASSERTIONS_ENABLED
    #define BEGIN_ASSERT_LOCK_NOT_NECESSARY(L)         (L).Acquire();
    #define END_ASSERT_LOCK_NOT_NECESSARY(L)            (L).Release();
    #else
    #define BEGIN_ASSERT_LOCK_NOT_NECESSARY(L)
    #define END_ASSERT_LOCK_NOT_NECESSARY(L)
    #endif




#endif //_ASSERT_LOCK_H