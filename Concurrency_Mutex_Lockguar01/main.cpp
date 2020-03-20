#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include <string_view>
#include <chrono>


std::string time() {
    static auto start=std::chrono::steady_clock::now();
    std::chrono::duration<double>d=std::chrono::steady_clock::now()-start;
    return "[" + std::to_string(d.count())+"s]";
}

std::mutex printMutex;

void print(std::string_view sv) {
    
    std::lock_guard<std::mutex>lg{printMutex};
    for(auto c:sv)
        std::cout.put(c);
    std::cout<<std::this_thread::get_id()<<'\n';  
}

int main()
{
    std::cout<<"time at start: "<<time()<<'\n';
    
    std::future<void>f1=std::async(std::launch::async, print, "Hello from the first thread...");
    auto f2=std::async(std::launch::async, print, "Hello from the second thread...");

    print("Hello from the main thread");
    
    
    std::cout<<"time at end: "<<time()<<'\n';
    
    return 0;
}
