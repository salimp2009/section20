#include <iostream>
#include <thread>
#include <mutex>
#include <memory>



class MySingleton {
private:
    inline static std::once_flag initInstanceFlag{};
    inline static MySingleton* instance{nullptr};
    MySingleton()=default;
    ~MySingleton()=default;
    
public:
    MySingleton(const MySingleton&)=delete;
    MySingleton& operator=(const MySingleton&)=delete;
    
    static MySingleton* getInstance(){
        std::call_once(initInstanceFlag, MySingleton::initSingleton);
        std::cout<<"Initializing Singleton()..\n";
        return instance;
    }
    
    static void initSingleton() {
        instance=new MySingleton();
        
    }
    
    void close() { this->~MySingleton();}

};

    //MySingleton* MySingleton::instance=nullptr;
    // std::once_flag MySingleton::initInstanceFlag; 

class MeyerSingleton{
public:
    static MeyerSingleton& getInstance() {
        static MeyerSingleton instance;
        return instance;
    }
private:
    MeyerSingleton()=default;
    ~MeyerSingleton()=default;
    MeyerSingleton(const MeyerSingleton&)=default;
    MeyerSingleton& operator=(const MeyerSingleton&)=default;
    
}; 

int main()
{
    std::cout<<'\n';
    
    std::cout<<"MySingleton::getInstance(): "<<MySingleton::getInstance()<<'\n';
    std::cout<<"MySingleton::getInstance(): "<<MySingleton::getInstance()<<'\n';
    
    std::cout<<"MeyerSingleton::getInstance(): "<<&MeyerSingleton::getInstance()<<'\n';
    std::cout<<"MeyerSingleton::getInstance(): "<<&MeyerSingleton::getInstance()<<'\n';
    
    std::cout<<'\n';

    return 0;
}
