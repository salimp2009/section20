#include <iostream>
#include <thread>
#include <chrono>
#include <exception>
#include <stdexcept>
#include <random>
#include <string>
#include <future>

std::thread::id masterThreadID;

//void do_Something(int num, char c) {
//    try {
//        std::random_device rd;
//        std::mt19937 mtwister(rd()*c);
//        std::uniform_int_distribution<int> uid(10, 1000);
//        std::this_thread::sleep_for(std::chrono::milliseconds(uid(mtwister)));
//        if(masterThreadID==std::this_thread::get_id()) {
//            std::cout<<"this is master thread: "<<std::this_thread::get_id()<<'\n';
//        }
//        for(int i{0}; i<num; ++i)
//            std::cout.put(c).flush();
//    } catch(const std::exception& e) 
//    {
//        std::cout<<"\nThread Exception: "<<" thread id: "
//                 <<std::this_thread::get_id()<<'\n';
//        
//    }
//}


void do_Something2(std::promise<std::string>& p) 
{
    try {
        // read from the console 
        std::cout<<"enter a char (x for exception example): ";
        char c=std::cin.get();
        
        // throw if 'x' is entered
        if(c=='x') throw std::runtime_error(std::string("char")+c+"read");
       
      // if everything ok, pass the read value and std::promise will set_value
      // so the value can be read from the calling main / function
      std::string s=std::string("char ")+c+" processed\n";
      p.set_value(std::move(s));
    //  p.set_value_at_thread_exit(std::move(s))  // alternative set ; it sets the value 
                                                  // at the exit so the main program will get until function is exited
    } catch(...)                                  // similar option is also available for the exception
    {
      p.set_exception(std::current_exception());  // store the exception in promise
    }
}

int main()
{
    try {
//        std::thread t1(do_Something, 5, '.');
//        masterThreadID=t1.get_id();
        
        //std::promise is another object that is passed into function with a thread
        // and it  hold a value or catches the exceptipn..
        // with promise mechanism we can retrieve the data from the thread like std::future
        std::promise<std::string>p;
        std::thread t2(do_Something2, std::ref(p));
        t2.detach();
        
        // create a future to get the result from the promise when needed
        std::future<std::string>f{p.get_future()};
        
        // process the outcome from the promise and use the future to access the result
        std::cout<<"result from the promise: "<<f.get();
        
        //returning the possible number of threads
        std::cout<<std::thread::hardware_concurrency();
        
        // you can get() only once
        //f.get();                      // runtime error
        
//        std::cout<<" starting thread id: "<<t1.get_id()<<'\n';
//        
//        for(int i{0}; i<5; ++i) {
//            std::thread t(do_Something, 10, 'a'+i);
//            std::cout<<"--starting to detach thread ID: "<<t.get_id()<<'\n';
//            t.detach();                                                         // detach() sends the thread to background but not recommended
//        }
        
//        std::cin.get();  // give time to threads to finish then press enter
        
//        std::cout<<"--joining thread ID: "<<t1.get_id()<<'\n';
//        t1.join();
    } catch(const std::exception& e) {
        std::cerr<<"Exception caught..."<<e.what()<<'\n';
    } catch(...) {
        std::cout<<"EXCEPTION....!!!\n";
    }

    return 0;
}
