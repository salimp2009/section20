#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include <string_view>
#include <chrono>

bool readyFlag{false};
std::mutex readyFlagMutex;


void thread1() 
{
    std::lock_guard<std::mutex>lg(readyFlagMutex);
    readyFlag=true;
    std::cout<<"ready flag/data is ready"<<'\n'
             <<"\t thread id: "<<std::this_thread::get_id()<<'\n';
}  // lock is released at the exit of the function

void thread2() 
{
    {   // try to lock if possible
        std::unique_lock<std::mutex>ulck(readyFlagMutex);       // unique_lock<> locks only when the lock is available otherwise
        // wait until mutex is available                        // it owns the mutex and locks when the mutex/lock is available
        while(!readyFlag) {                        
            ulck.unlock();
            std::this_thread::yield();      // give access to next thread
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ulck.lock();                    // try to lock; if not available it blocks
        }
    
    // we used the data 
    readyFlag=false;
    std::cout<<"\nData used..readyFlag=false "<<'\n'
              <<"\t thread id: "<<std::this_thread::get_id()<<'\n';


    } // lock is released here; that is why we need to put extra scope paranthesis 
      //if you want to release the lock before function exit

     // here do whatever should happen after thread 1 has prepared things...
}
         
int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();

    return 0;
}
