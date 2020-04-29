#include <iostream>
#include "AssertLock.hpp"
#include <stdio.h>
#include <thread>
#include <cassert>
#include <vector>
#include <memory>

// volatile is NOT ATOMIC but it will let us to detect if there were any attemps ; defined in AssertLock class
  // tif there are any overlaps between two critical sections if not then we dont need to lock
  // but if there is one thread will change the lock and when the other thread tries before it is released
  // assert will throw an error and programmer can determine which sections should be locked
  // However to get a 90% correctness rate we need to get a big team of developers(100+) run it 
  // multiple times during the day

// Somehow ASSERTIONS ARE NOT ENABLED; will try on Visual Studio
#define ASSERTIONS_ENABLED

AssertLock g_lock;

 void CriticalOperation(int n) 
 {
        BEGIN_ASSERT_LOCK_NOT_NECESSARY(g_lock);
        std::cout<<"thread no: "<<n<<'\n';
        printf("performing critical operation...\n");
        END_ASSERT_LOCK_NOT_NECESSARY(g_lock);
 }


int main()
{
    std::thread t1(CriticalOperation, 1);
    CriticalOperation(2);
    
    t1.join();

    return 0;
}
