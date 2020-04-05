#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> count{0};

void add() 
{
    for(int n{0}; n<1000; ++n)
        count.fetch_add(1, std::memory_order_relaxed);      // add operation is processed atomically 
                                                            // and no sequence or ordering between threads
                                                            // and wait free-lock free; no data race
}

int main()
{
    std::vector<std::thread> threads;
    for(std::size_t n{0}; n<10; ++n) 
        threads.emplace_back(add);
        
    for(auto& t:threads)
        t.join();
    
    std::cout<<"Final value of counter: "<<count<<'\n';

    return 0;
}
