#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <exception>
#include <random>
#include <deque>
#include <numeric>
class SumUp {
public:
    int operator()(int beg, int end) {
        long long int sum{0};
        for(int i{beg}; i<end; ++i) sum+=i;
        return sum;
    }
};

int main()
{
    SumUp sumUp1;
    SumUp sumUp2;
    SumUp sumUp3;
    SumUp sumUp4;
    SumUp sumUp5;
    
    // create seperate package_task and pass the function object
    // the type of package task should match the function signature (return type and type of arguments)
    std::packaged_task<int(int, int)> pTask1(sumUp1);
    std::packaged_task<int(int, int)> pTask2(sumUp2);
    std::packaged_task<int(int, int)> pTask3(sumUp3);
    std::packaged_task<int(int, int)> pTask4(sumUp4);
    std::packaged_task<int(int, int)> pTask5(sumUp5);
    
    // create  seperate futures  and tie the to each package task
    // the type of the future should match the type of the returned value from packaged task
    std::future<int>fut1=pTask1.get_future();
    std::future<int>fut2=pTask2.get_future();
    std::future<int>fut3=pTask3.get_future();
    std::future<int>fut4=pTask4.get_future();
    
    // put the packaged_tasks into a container to be processed later
    using  pTaskInt = std::packaged_task<int(int, int)>;
    std::deque<pTaskInt> all_packTasks;
    all_packTasks.push_back(std::move(pTask1));
    all_packTasks.push_back(std::move(pTask2));
    all_packTasks.push_back(std::move(pTask3));
    all_packTasks.push_back(std::move(pTask4));

    // set values to be summed up by each thread
    int begin{1};
    int increment{2500};
    int end=begin+increment;    // end value will be updated for each thread; begin value will change after each task
    
    while(!all_packTasks.empty()) {
        // start getting tasks out of container and pass it to a seperate thread
        std::packaged_task<int(int, int)>currentTask=std::move(all_packTasks.front());
        all_packTasks.pop_front();
        // create a thread and pass the current task and the value to be used in the function that 
        // the function will take (int begin, int end)
        std::thread sumThread(std::move(currentTask), begin, end);
        begin=end;                                                          // update the values to be used in next thread
        end+=increment;
        sumThread.detach();
    }
    
    
    // get the results via future
   auto sum=fut1.get()+fut2.get()+fut3.get()+fut4.get();
    
  std::cout<<"sum of 0... 10000= "<<sum<<'\n';
    
    std::cout<<'\n';
    
    
    


    return 0;
}
