#include <iostream>
#include <future>
#include <thread>
#include <utility>

std::mutex coutMutex;

struct Div {
  void operator()(std::promise<int>&& intPromise, int a, int b) const {
      intPromise.set_value(a/b);
  }  
};

struct Requestor {
  void operator()(std::shared_future<int> sharFut)  const {
      // lock the critical section: std::cout
      std::lock_guard coutGuard(coutMutex);
      
      // print the thread id
      std::cout<<"thread id: "<<std::this_thread::get_id()<<'\n';
      
      // get the result from shared_future object; every thread will get the same value
      // as long as the values passed into share_future are not references
      std::cout<<"\t div result: "<<sharFut.get()<<'\n';
  }  
};

int main()
{
    std::promise<int>divPromise;
    
    std::shared_future<int> sharFut=divPromise.get_future();
    
    
    // calculate the division and store the result in promise object
    // the stored value of promise can be accessed thru shared_future object
    // the state/stored value of shared_future object is accessible multiple times
    std::thread t1(Div{}, std::move(divPromise), 20, 10);
    
 
    // get the division results stored in shared futured
    // with seperate threads
    std::thread t2(Requestor{}, sharFut);
    std::thread t3(Requestor{}, sharFut);
    std::thread t4(Requestor{}, sharFut);
    std::thread t5(Requestor{}, sharFut);
    
    // call all the child threads to the parent main thread
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    
    return 0;
}
