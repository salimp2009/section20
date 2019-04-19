#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

class Sleeper {
public:
    Sleeper(int& val):i{val}{ }
    void operator()(int k) {
        for(std::size_t j{0}; j<=5; ++j) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            i+=k;
        }
        std::cout<<std::this_thread::get_id()<<'\n';
    }
private:
    int& i;
};

int main()
{
    std::cout<<std::boolalpha<<'\n';
    
    int valSleeper=1000;
    
    std::thread t1(Sleeper{valSleeper}, 5);
    
    std::cout<<std::setw(20)<<std::left<<"\nJoinable: "<<t1.joinable()<<'\n';
    
    std::cout<<std::setw(20)<<std::left<<"\nPossible threads: "<<std::thread::hardware_concurrency()<<'\n';
    
    t1.join();
    
    std::cout<<std::setw(20)<<std::left<<"\nvalSleeper= "<<valSleeper<<'\n';
    
    std::cout<<'\n';
 
 return 0;
}