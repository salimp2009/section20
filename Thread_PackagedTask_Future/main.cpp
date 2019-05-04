#include <iostream>
#include <thread>
#include <deque>
#include <future>
#include <functional>
#include <utility>
#include <exception>

// Sample for Packaged Tasks, Future and Thread 
// from book "Concurency with Modern C++" by Rainer Grimm (page 137, 2019 edition)


// create a callable function to calculate sum with the give range
class SumUp 
{
public:
    int operator()(std::size_t beg, std::size_t end) {
        long long int sum{0};
        try{
            for(std::size_t i=beg; i<end; ++i) sum+=i; 
            std::cout<<"\nThread ID: "<<std::this_thread::get_id()<<std::endl;
        } catch(const std::exception& e) {
            std::cerr<<"\nException: "<<e.what()
            <<"Thread ID: "<<std::this_thread::get_id()<<'\n';
        } catch(...) {
            std::cerr<<"\nException: "
            <<"Thread ID: "<<std::this_thread::get_id()<<'\n';
        }   
        return sum; 
    }
};


int main()
{
    try{
        // create 4 objects of the callable function to be used in different tasks and thread
        SumUp sumUp1;
        SumUp sumUp2;
        SumUp sumUp3;
        SumUp sumUp4;
        
        // create a packaged task with the same type of callable ogject (function)
        std::packaged_task<int(std::size_t, std::size_t)>sumTask1(sumUp1);  // assign a function to each taskß
        std::packaged_task<int(std::size_t, std::size_t)>sumTask2(sumUp2);
        std::packaged_task<int(std::size_t, std::size_t)>sumTask3(sumUp3);
        std::packaged_task<int(std::size_t, std::size_t)>sumTask4(sumUp4);
        
        // create future objects that will get the value of packaged Tasks
        std::future<int>sumResult1 = sumTask1.get_future();
        std::future<int>sumResult2 = sumTask2.get_future();
        std::future<int>sumResult3 = sumTask3.get_future();
        std::future<int>sumResult4 = sumTask4.get_future();
        
        // store all Tasks in a container; deque
        std::deque<std::packaged_task<int(std::size_t, std::size_t)>>AllTasks;
        
        // move all packaged Tasks into container; 
        // Tasks cannot be copied therefore std::move has to be used!!
        AllTasks.push_back(std::move(sumTask1));
        AllTasks.push_back(std::move(sumTask2));
        AllTasks.push_back(std::move(sumTask3));
        AllTasks.push_back(std::move(sumTask4));
        
        std::size_t begin{1};
        std::size_t increment{2500};
        std::size_t end = begin+increment;
        
        while(!AllTasks.empty()) {
            std::packaged_task<int(std::size_t, std::size_t)>myTask=std::move(AllTasks.front());  // move the task from container to new task
            AllTasks.pop_front();                                                                 // remove the front element since it is moved
            std::thread sumThread(std::move(myTask), begin, end);                                 // move the new task to a thread with arguments
            begin=end;                                                                            // change the end adn begin for the new task and thread
            end+=increment;
           // std::cout<<"\nThread ID: "<<sumThread.get_id()<<std::endl;
            sumThread.detach();                                                                   // send the thread to background; detach
        }
        
        
        // alternative way for the loop to create Threads and assign tasks from the container
        // Note: std::move() has to be used to transfer tasks to threads because
        // tasks are not copyable therefore need to remove that element from the container
//        for(auto& task:AllTasks) {
//            std::thread sumThread(std::move(task), begin, end);
//            AllTasks.pop_front();
//            begin=end;
//            end+=increment;
//            sumThread.detach();
//        }

        //  a static member function that returns possible number of parallel threads:
        // • Returns the number of possible threads.
        // • This value is just a hint and does not guarantee to be exact.
        // • Returns 0 if the number is not computable or well defined.
        unsigned int num_conc =std::thread::hardware_concurrency();             
        std::cout<<"\nNumber of thread running concurent : "<<num_conc<<'\n';
        
        // get the results
        auto sum= sumResult1.get()+sumResult2.get()+
                  sumResult3.get()+sumResult4.get();

        std::cout<<"sum of 0 to 10,000 is: "<<sum<<'\n';
    
    }catch(const std::exception& e) {
        std::cerr<<"\nEXCEPTION: "<<e.what()<<'\n';
        
    }catch(...) {
        std::cerr<<"error..\n";
    }
    
    std::cout<<"\nFinishing program...\n";
    
 return 0;
}