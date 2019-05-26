#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <exception>
#include <mutex>
#include <thread>
#include <stack>
#include <atomic>


struct empty_stack: std::exception
{
    virtual const char* what() const throw() {
        return "\nread empty stack..!!!\n";
    }
};

template<typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack(){ }
    
    // copy constructor to be protected while the dataa of other is copied into new stack
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data=other.data;
    }
    
    // copy assignment is not allowed
    threadsafe_stack& operator=(const threadsafe_stack&)=delete;
    
    T top() const
    {
        std::lock_guard<std::mutex>lock(m);             // lock before pushing
        return data.top();
    }
    
    
    void push( T new_value)
    {
        std::lock_guard<std::mutex>lock(m);             // lock before pushing
        data.push(new_value);
    }
    
    // use shared pointer to make a copy the top() on the heap before pop()
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex>lock(m);
        if(data.empty()) throw empty_stack();
        std::shared_ptr<T> const res=std::make_shared<T>(data.top());
        data.pop();
        return res;
    }
    
    
    // Alternative method to pop and return the value by reference
    void pop(T& result)                         
    {
        std::lock_guard<std::mutex>lock(m);
        if(data.empty()) throw empty_stack();
        result=data.top();
        data.pop();

    }
 
    bool empty() {
        std::lock_guard<std::mutex> lock(m);        // lock before checking because other threads
        return data.empty();                        // might pop or push and status can change
        
    } 
};

int main()
{
    threadsafe_stack<int>my_stack;
   
   try {
   std::thread t3([](threadsafe_stack<int>&my_stack){ my_stack.push(40);}, std::ref(my_stack));   
   std::thread t1([](threadsafe_stack<int>&my_stack){ my_stack.push(50);}, std::ref(my_stack)); 
   std::thread t2([](threadsafe_stack<int>&my_stack){ my_stack.push(60);}, std::ref(my_stack)); 
   std::thread t4([](threadsafe_stack<int>&my_stack){ my_stack.pop();}, std::ref(my_stack));
    
    t3.join();  
    t1.join();
    t2.join();
    t4.join();
    
 // my_stack.push(20);
   
  std::cout<<my_stack.top()<<'\n';
  auto m=my_stack.pop();
  std::cout<<*m<<'\n';  
   } catch(...) {
       std::cerr<<"\nError: empty stack!!!..\n";
   }
   
   std::shared_ptr<int>some_ptr=std::make_shared<int>(42);
   
  std::cout<<"\nAtomic check: "<<std::atomic_is_lock_free(&some_ptr)<<'\n';
 
 return 0;
}