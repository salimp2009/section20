#include <iostream>
#include <future>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <queue>

// CONDITION VARIABLE EXAMPLE 2
// Better example than 1
// There is a bug in this program; thread 1 never finishes and program does not terminate
// the consumer thread keeps waiting for CondVar.wait(); it might be because of while(true) loop

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondVar;

// will provide items for consumers and send it to consumers 
// everytime a product is ready without waiting (only a silght delay in between each product)
// all products to be ready; there will be several providers and several consumers

void provider(int val)
{
 // push items (val+i) into queue and send it to consumer 
 // and wait for val miliseconds to provide the next item    
    for(int i{0}; i<6; ++i) {
         {
             std::lock_guard<std::mutex> lg(queueMutex);
             queue.push(val+i);
    //       std::cout<<"\nProvided item no: "<<i<<" Provider no: "<<std::this_thread::get_id()<<'\n'; 
         } // release lock
         queueCondVar.notify_one();
         
         std::this_thread::sleep_for(std::chrono::milliseconds(val));
         
     }   
//      std::cout<<"\nProvided all items..(provider no: "<<std::this_thread::get_id()<<")\n";
}


// consumers will get the items (when each one is ready) 
// provided by Provider and use a certain amount of it
// there will be several consumers

void consumer(int num)
{
    while(true) {          
        int val{0};
        {
            std::unique_lock<std::mutex>ul(queueMutex);
            queueCondVar.wait(ul, [](){ return !queue.empty(); });  // unique lock will wait until wait() and the condition in the lambda becomes true
            val=queue.front();                                      // use the value sent by provider
            queue.pop();                                            // delete the val from que to avoid infinite loop
            
         //std::cout<<"\nConsumer no: "<<num<<" consumed :"<<val<<"\nthread id: "<<std::this_thread::get_id()<<'\n';
            
        } // release lock
       
         std::cout<<"\nconsumer "<<num<<": "<<val<<" "<<std::this_thread::get_id()<<'\n';    
    }
}

// main program will send several providers and consumers
int main()
{
    
    // start three providers for values for 100+, 300+, 500++
    auto p1=std::async(std::launch::async, provider, 100);
    auto p2=std::async(std::launch::async, provider, 300);
    auto p3=std::async(std::launch::async, provider, 500);
    
    // start 2 consumers printing/consuming the values/items and consumer no + thread id
    auto c1=std::async(std::launch::async, consumer, 1);
    auto c2=std::async(std::launch::async, consumer, 2);
    
    
 return 0;
}
