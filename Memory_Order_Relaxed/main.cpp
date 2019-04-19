#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

// Memory order relaxed example;
// there is no sync or locks therefore it is important
// to have your program logic should not matter the order of execution
// counter is an example where it is incremented but the order it is 
// incremented doesnot matter. 
// there is syncronization at .join() part of the program

// atomic number count is incremented using the relaxed semantic, 
// so we have a guarantee that the operation is atomic. 
// The fetch_add operation establishes an ordering on count. 
// The function add() is the work package of the threads.
// Each thread gets its work package

// Thread creation is one synchronisation point. 
// And other one is t.join()
// The creator thread synchronises with all its children
// It waits with the t.join() call until all its children are done. 
// t.join() is the reason that the results of the atomic operations 
// are published; t.join() is a release operation.

// In conclusion, there is a happens-before relation between 
// the increment operation and the reading of the counter count at
// the end of the program

// this algorithm is not only lock-free but it is also wait-free.


std::atomic<int>count{0};

void add() {
    for(std::size_t i{0}; i<1000; ++i)
        count.fetch_add(1, std::memory_order_relaxed);
}

int main()
{
    std::vector<std::thread>all_threads;
    for(std::size_t i{0}; i<10; ++i) {
        all_threads.emplace_back(add);
    }
    
    for(auto& t:all_threads) {
        t.join();
    }
    
    std::cout<<"\nFinal counter value is "<<count<<'\n';
    
 return 0;
}
