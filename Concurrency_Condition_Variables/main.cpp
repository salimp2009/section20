#include <iostream>
#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>

bool readyFlag{false};
std::mutex readyMutex;
std::condition_variable readyCondVar;

void writerThread1()
{
    std::cout<<"Please enter <return> reader needs preparation....\n";
    std::cin.get();
    
    // lock the critical data, prepare data and set the boolean to be ready & release the lock
    {
        std::lock_guard<std::mutex>lck(readyMutex);  // lock_guard is used for the writer thread because it has to lock
        readyFlag=true;  
                                                    // as soon as mutex available; reader will use unique_lock since it will not lock immediately   
    } // release the flag 
    
    std::cout<<"writer done....\n";
    readyCondVar.notify_one();                       // send signal to waiting reader thread; 
                                                    // if more than one thread is used notify_all() should be used 
    
}

void readerThread2()
{
    // wait until thread1 has prepared and signaled condition
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        readyCondVar.wait(ul, [](){ return readyFlag; });   // checkConVar for signal if it is true 
                                                            // then check if the readyFlag is true also for a second confiormation
                                                           // the second check is neccessary because the system/library  might do
                                                           // a random wakeup call to prevent thread  missing a condition which might cause
                                                           // too many cycles
    }  // release the lock
    
    // do whatever after
    std::cout<<"reader done....\n";   
}

int main()
{
    // create two threads using future/async 
    // no need to call futures by get() into main since the functions do not
    // return any value;
    auto f1=std::async(std::launch::async, writerThread1);
    auto f2=std::async(std::launch::async, readerThread2);

    return 0;
}
