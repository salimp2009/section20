#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

struct CriticalData {
    std::mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b) {
    
    // Alternative; using std::scoped_lock
//    std::cout<<"\nThread: "<<std::this_thread::get_id()<<" First mutex\n";
//    std::this_thread::sleep_for(std::chrono::milliseconds(1));
//    std::cout<<"\n  Thread: "<<std::this_thread::get_id()<<" Second mutex\n";
//    std::cout<<"\n    Thread: "<<std::this_thread::get_id()<<" Get both mutexes\n";
//    
//    std::scoped_lock(a.mut, b.mut);
//    std::cout<<"\n    Thread: "<<std::this_thread::get_id()<<" Got both mutexes\n";
    
    
    // Alternative way of locking first both mutexes; both metohds avoid deadlocks
//    std::lock(a.mut, b.mut);
//    std::unique_lock<std::mutex> guard1(a.mut, std::adopt_lock);
//    std::unique_lock<std::mutex> guard2(b.mut, std::adopt_lock);
//    std::cout<<"\nThread: "<<std::this_thread::get_id()<<'\n';
//    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
     // Deferred way of locking after creating the lock_guards;
    std::unique_lock<std::mutex> guard1(a.mut, std::defer_lock);        // gets the ownership of mutex but does not lock
    std::cout<<"\nThread: "<<std::this_thread::get_id()<<'\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
    std::unique_lock<std::mutex> guard2(b.mut, std::defer_lock);        // gets the ownership of mutex but does not lock
    std::cout<<"\nThread: "<<std::this_thread::get_id()<<'\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
    std::lock(guard1, guard2);                                          // lock both mutexes; or none if not possible
    std::cout<<"\nLocked by Thread: "<<std::this_thread::get_id()<<'\n';
    // do something with a & b
}
// locks released by default destructor

int main()
{
    
    CriticalData c1{};
    CriticalData c2{};
    
    std::thread t1(deadLock, std::ref(c1), std::ref(c2));    // std::ref() is needed since function expects reference
    std::thread t2(deadLock, std::ref(c2), std::ref(c1));
    
//    std::thread t1([&](){deadLock(c1,c2);});              // alternative way of calling function using lambda
//    std::thread t2([&](){deadLock(c2,c1);});              
    
    t1.join();
    t2.join();
    
    std::cout<<"\nFinishing program...\n";
    std::cout<<'\n';

 return 0;
}