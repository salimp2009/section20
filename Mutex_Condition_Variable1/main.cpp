#include <iostream>
#include <mutex>
#include <future>
#include <condition_variable>

// CONDITION VARIABLE EXAMPLE 
// Note: not an ideal example only for general idea how to use; 
// see second CondVar2 example for a better implemantation

bool readyFlag{false};
std::mutex readyMutex;
std::condition_variable readyCondVar;

void thread1()
{
    // do something as thread 2 needs....
    std::cout<<" Press <return> "<<'\n';
    std::cin.get();
    
    // signal thread 2 the condition is ready 
    {
        // lock the mutex
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag=true;
        std::cout<<"\nCondition ready for thread 2..\n";
        
    } // release the lock
    
    // notify thread 2; condition ready
    readyCondVar.notify_one(); 
    std::cout<<"\nThread 2 notified...\n"; 
}

void thread2()
{
    // wait until thread 1 is ready
    {
        std::unique_lock<std::mutex>ul(readyMutex);     // we have to use a unique_lock and can’t use a lock_guard here, 
                                                        // because inter- nally, wait() explicitly unlocks 
                                                        // and locks the mutex.
        readyCondVar.wait(ul, []{ return readyFlag;});  // wait() function internally checks 
                                                        // if Variable condition is ready, the lambda function
    } // release lock                                   // is used for a secondary check by returning the of flag
                                                        // only using wait() internal check is riskier
                                                        
    // do whatever needs to be done after thread 1 has prepared thing 
    
    std::cout<<"\nThread 2 Done...\n";    
}



int main()
{
    std::future<void>f1=std::async(std::launch::async, thread1);
    std::future<void>f2=std::async(std::launch::async, thread2);
    
    std::cout<<"\nThe main thread is also working....\n";
    
//    f1.get();
//    f2.get();
    
    std::cout<<"\nMain thread done..\n";
 
 return 0;
}