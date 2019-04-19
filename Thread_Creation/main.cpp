#include <iostream>
#include <thread>

// Example for Basic Thread creation and join()

void helloFunction() {
    
    std::cout<<"\nHello Function...Thread ID: "<<std::this_thread::get_id()<<'\n';
}

class HelloFunctionObject {
public:
    void operator()()const {
        std::cout<<"\nHello from Function object....Thread ID: "<<std::this_thread::get_id()<<'\n';
    }
};
int main()
{
    HelloFunctionObject functobj{};
    std::thread t1(helloFunction);
    std::thread t2(functobj);
    std::thread t3([](){std::cout<<"\nLamda function..Thread ID: "
                                 <<std::this_thread::get_id()<<'\n';} );
    
    t1.join();      // if the .join() is not supplied the program will terminate with error
    t2.join();      // to be able to get the results of the threads we have to use join or
    t3.join();      // or use promises to store the results and get results via future
 
 return 0;
}