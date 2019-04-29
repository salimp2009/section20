#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

// Example for Conditional Var;

// The predicate is a kind of memory for the stateless condition variable; 
// therefore, the wait call always checks the predicate at first. 
// Condition variables are victim to two known phenomena: lost wakeup and spurious wakeup.
// Lost Wakeup;
    // The phenomenon of the lost wakeup is that the sender sends its notification 
    // before the receiver gets to its wait state. The consequence is that the notification is lost. 
    // The C++ standard describes condition variables as a simultaneous synchronisation mechanism: 
    // “The condition_variable class is a synchronisation primitive that can be used to block a thread, 
    // or multiple threads at the same time, ...”. So the notification gets lost, and 
    // the receiver is waiting and waiting and ... .
// Spurious Wakeup;
    // It may happen that the receiver wakes up, although no notification happened. 
    // At a minimum POSIX Threads and the Windows API can be victims of these phenomena. 
    // One reason for a spurious wakeup can be a stolen wakeup. 
    // This means, before the awoken thread gets the chance to run, another thread kicks in and runs.
    
// std::unique_lock<std::mutex> lck(mutex_): In the initial processing, 
// the thread locks the mutex and then check the predicate []{ return dataReady; }.
// If the call of the predicated evaluates to
// * true: the thread continues its work.
// * false: condVar.wait() unlocks the mutex and puts the thread in a waiting (blocking)
// state


std::mutex mutex_;
std::condition_variable condVar;

bool dataReady{false};

void doTheWork(){
    std::cout<<"\nProcessing shared data..\n";
}

void waitingForWork() {
    std::cout<<"\nWorker: waiting for work...\n";
    
    std::unique_lock<std::mutex>lck(mutex_);                // unique lock needs to be used here since we are using wait() with
    condVar.wait(lck, [](){ return dataReady;});            // conditional variable
    doTheWork();
    std::cout<<"\nWorker: work done...\n";
    
}

void setDataReady() {
    {
        std::lock_guard<std::mutex>lck(mutex_);
        dataReady=true;
    }
    std::cout<<"\nSender: Data ready..."<<std::this_thread::get_id()<<'\n';
    condVar.notify_one();
}

int main()
{
    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);
    
    std::cout<<"\nMain is working too..."<<std::this_thread::get_id()<<'\n';
    
    t1.join();
    t2.join();
 
 
 return 0;
}