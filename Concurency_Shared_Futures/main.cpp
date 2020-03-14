#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <exception>
#include <random>
#include <string>

std::string time() {
    static auto start=std::chrono::steady_clock::now();
    std::chrono::duration<double>d=std::chrono::steady_clock::now()-start;
    return "[" + std::to_string(d.count())+"s]";
}

int querrynumber() {
    
    std::cout<<"enter a number: ";
    int num;
    std::cin>>num;
    
    if(!std::cin) throw std::runtime_error("no valid number..");
    
    return num;
}

//shared_future can be passed as const& as well but risky 
// for lifetime and data race issues; passing by value is expensive but better than having bugs
void doSomething(char c, std::shared_future<int> f) 
{

    try {
        int num=f.get();
        
        for(int i{0}; i<num; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout.put(c).flush();
        }
        std::cout<<"\nThread ID: "<<std::this_thread::get_id()<<'\n';

    } catch(const std::exception& e) {
            std::cerr<<"exception in thread: "<<std::this_thread::get_id()
                     <<": "<<e.what()<<'\n';
    }
}

int main()
{
    try {
        std::cout<<"Starting program at: "<<time()<<'\n';
        std::shared_future<int>f=std::async(std::launch::async, querrynumber);
        
        
        // the shared_future can be used as a reference if the receiving function
        // is by const& ; in that case pass by std::ref(f) wrapper
        auto f1=std::async(std::launch::async,doSomething, '.', f);
        auto f2=std::async(std::launch::async,doSomething, '+', f);
        auto f3=std::async(std::launch::async,doSomething, 'x', f);
        
        f1.get();
        f2.get();
        f3.get();
    
    } catch(const std::exception& e) {
        std::cerr<<"error caught in main: "<<e.what()<<'\n';
    }
    std::cout<<"Finishing program at: "<<time()<<'\n';
    
    return 0;
}
