#include <iostream>
#include <thread>
#include <mutex>

// Example with Once_Flag;

// By using the std::call_once function, you can register a callable.
// The std::once_flag ensures that only one registered function is invoked. 
// You can register additional functions via the same std::once_flag. 
// Only one function from that group is called.

// std::call_once obeys the following rules:
// • Exactly one execution of exactly one of the functions is performed. 
//   It is undefined which function is selected for execution. 
//   The selected function runs in the same thread as the 
//   std::call_once invocation it was passed to.
// • No invocation in the group returns before the above-mentioned 
//   execution of the selected function completes successfully.
// • If the selected function exits via an exception,
//   it is propagated to the caller and Another function selected and executed. 

std::once_flag onceFlag;

void do_once() {
    std::call_once(onceFlag, [](){std::cout<<"\nOnly Once...\n";});
}

void do_once2() {
    std::call_once(onceFlag, [](){std::cout<<"\nOnly Once2...\n";});
}

int main()
{
    std::cout<<'\n';
    
    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once2);
    std::thread t4(do_once2);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    std::cout<<'\n';
  
 return 0;
}