#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <queue>

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
  for(int i{0}; i<6; ++i) 
  {
    {
      std::lock_guard<std::mutex>lck(queueMutex);
      queue.push(val+i);
    } // release.lock
    queueCondVar.notify_one();      // notify the data is ready so consumer can start reading
    std::this_thread::sleep_for(std::chrono::milliseconds(val));  // give access to other threads to write to que
  }
}

void consumer(int consumerNum) 
{
    // use the val from the queue and pop it
    
    do 
    {
        int consumeVal{0};
       { 
          std::unique_lock<std::mutex>ul(queueMutex);
          queueCondVar.wait(ul, [](){ return !queue.empty();});
          consumeVal=queue.front();
          queue.pop();
        } // release lock

        std::cout<<"consumer no: "<<consumerNum<<", val: "<<consumeVal<<'\n';
        
    } while(true); // run continuously
}
int main()
{
    // start three providers
    auto p1=std::async(std::launch::async, provider, 100);
    auto p2=std::async(std::launch::async, provider, 300);
    auto p3=std::async(std::launch::async, provider, 500);
    
    // start two consumers 
    auto c1=std::async(std::launch::async, consumer, 1);
    auto c2=std::async(std::launch::async, consumer, 2);
    
    return 0;
}
