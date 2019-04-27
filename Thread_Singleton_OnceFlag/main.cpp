#include <iostream>
#include <mutex>
#include <atomic>
// Example for Thread Safe Singleton Object;
// Singleton is an object that can be initialized once and have only one single instance;
// No copy constructor or assignment operator allowed
// Alternative method is to use Scott_Meyer's Singleton method; using only static variable; no pointer

class MySingleton {
private:
    static std::once_flag initInstanceFlag;
    static MySingleton* instance;
    MySingleton()=default;                                  
    ~MySingleton()=default;
public:
    MySingleton(const MySingleton&)=delete;                           // no copy constructor
    MySingleton& operator=(const MySingleton&)=delete;                // no copy assignment
    
    static MySingleton* getInstance() {                                 
        std::call_once(initInstanceFlag, MySingleton::initSingleton); // std::call_once guarantees that function is called once
        return instance;                                              // therefore initialization will happen only once 
    }
    
    static void initSingleton() {                                   // function will initialize the pointer with A
        instance= new MySingleton();                                // Singleton object on the heap
    }                                                               // since this function can be called once there will be only
};                                                                  // only one instance of object; no copy is allowed(deleted)

MySingleton* MySingleton::instance=nullptr;                         // the non-const static objects can be initialized outside the
std::once_flag MySingleton::initInstanceFlag;                       // class declaration

int main()
{
    std::cout<<'\n';
    
    std::cout<<"\nMySingleton::getinstance(): "<<MySingleton::getInstance()<<'\n';    // both will display the same pointer
    std::cout<<"\nMySingleton::getinstance(): "<<MySingleton::getInstance()<<'\n';    // because it will be initialized only once;
    
    std::shared_ptr<int>some_shrd_ptr;
    
    std::cout<<std::atomic_is_lock_free(&some_shrd_ptr);        // shared_pointers is not lock free
                                                                // C++20 might inlude lock free shared pointers
                                    
    std::cout<<'\n';
    
 return 0;
}