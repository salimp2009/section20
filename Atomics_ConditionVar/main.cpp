#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <mutex>

// Condition Variable Example;
// Condition variables may be victim to two phenomena:
// 1. spurious wakeup: the receiver of the message wakes up, 
// although no notification happened 
//2. lost wakeup: the sender sends its notification 
// before the receiver gets to a wait state.

std::vector<int> mySharedWork;
std::mutex mutex_;
std::condition_variable condVar;

bool dataReady{false};

void waitingForWork() {
    std::cout<<"\nWaiting for work..\n";
    {
        std::unique_lock<std::mutex>ul(mutex_);
        condVar.wait(ul, []{return dataReady;});
        mySharedWork[1]=2;
        std::cout<<"\nWork Done.."
                 <<"Thread ID: "<<std::this_thread::get_id()<<'\n';
    }
}

void setDataReady() {
    mySharedWork={1,0,3};
    {
        std::lock_guard<std::mutex>lg(mutex_);
        dataReady=true;
    }
     std::cout<<"\nData is ready.."
                 <<"Thread ID: "<<std::this_thread::get_id()<<'\n';
    condVar.notify_one();
}

int main()
{
    std::cout<<'\n';
    
    std::thread c1(waitingForWork);
    std::thread p1(setDataReady);
    
    
    std::cout<<"\nMain program is also working...\n";
    
    p1.join();
    c1.join();
    
    for(const auto& v: mySharedWork)
        std::cout<<v<<" ";
    
    std::cout<<"\nProgram finished...\n";
 
 return 0;
}