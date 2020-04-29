#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <utility>
#include <functional>



void calcProducts(std::packaged_task<int(int, int)>& task, const std::vector<std::pair<int, int>>& pairs)
{
        for(auto& elem:pairs) {
            auto fut=task.get_future();                                         // task will return to value to future         
            task(elem.first, elem.second);                                      // run the task with the assigned function
            std::cout<<elem.first<<" * "<<elem.second<<"= "<<fut.get()<<'\n';   // get the results via future get()
            task.reset();                                                       // the values in packaged_task will be reset to get another input / reuse
        }
}

int main()
{
    std::vector<std::pair<int, int>>allPairs;
    allPairs.push_back(std::make_pair(1,2));
    allPairs.push_back(std::make_pair(3,4));
    allPairs.push_back(std::make_pair(5,6));
    
    std::packaged_task<int(int, int)> task{[](int x, int y) { return x*y;}};

    std::cout<<'\n';
    // do the calculation in the main thread
    calcProducts(task, allPairs);
    
    std::cout<<'\n';
    
    std::thread t(calcProducts, std::ref(task), allPairs);      // calcFunction receives the vector as cont& to get it as a copy
    t.join();
    
    bool keys[10]={0};
    
    std::cout<<keys[10]<<'\n';
    
    for(auto c:keys)
        std::cout<<c<<" ";
    std::cout<<'\n';
    
    return 0;
}
