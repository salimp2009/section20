#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>
#include <csignal>

// std::atomic_signal_fence establishes memory synchronisation ordering of 
// non-atomic and relaxed atomic accesses between a thread and 
// a signal handler executed on the same thread

// signal() sets the handler for signal ; this is C function 
// The signal handler can be set so that default handling will occur,
// signal is ignored, or a user-defined function is called. In this example
// a function handler(int) is called to determine how the signal is handled.
// SIGTERM is a C Macro is a termination request for the program therefore,
// extern "C" specifier is used for the function signature

// Both std::atomic_signal_handler establish an acquire-release fence 
// between the release operation std::atomic_signal_fence(std::memory_order_release) 
// and the acquire operation std::atomic_signal_fence(std::memory_order_acquire)
// Therefore, release operations can not be reordered across the release fence
// and acquire operations can not be reordered across the acquire fence 
// the assertion assert(b.load(std::memory_order_relaxed)) 
// never fires because if a.store(true, std::memory_order_relaxed)  happens, 
// b.store(true, std::memory_- order_relaxed) must have happened before.


std::atomic<bool> a{false};
std::atomic<bool> b{false};


extern "C" void handler(int) {
    if(a.load(std::memory_order_relaxed)) {
        std::atomic_signal_fence(std::memory_order_acquire);  // fence guarantees the read operation happens before
        assert(b.load(std::memory_order_relaxed));
    }
}

int main()
{
    std::signal(SIGTERM, handler);
    
    b.store(true, std::memory_order_relaxed);
    std::atomic_signal_fence(std::memory_order_release);  // the fence guarantees write operation happens after and 
    a.store(true, std::memory_order_relaxed);             // the order of a.store does not change
                                                         // therefroe b.store happens before a.store and and 
                                                         // when the handler function is called b.load has to for aload to be true  
                                                         // this guarantees that b.load gets the correct value cause b.store has to happen 
                                                         // before a.store; if there was no fence then a.store could be reordered and
                                                         // b.load could have read the wrong value before b.store writes the right value
 return 0;
}