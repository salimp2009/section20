#include <iostream>

// Meyers Singleton Example;
// If you use the Meyers Singleton in a concurrent environment, 
// be sure that your compiler implements static variables with 
// the C++11 thread-safe semantic. 
// the compiler maynot support it. 
// The result may be that more than one instance of a singleton is created.

class MeyerSingleton {
public:
    static MeyerSingleton& getInstance() {
        static MeyerSingleton instance;
        return instance; 
    }
private:
    MeyerSingleton()=default;
    ~MeyerSingleton()=default;
    
    MeyerSingleton(const MeyerSingleton&)=delete;
    MeyerSingleton& operator=(const MeyerSingleton&)=delete;
};

int main()
{
   MeyerSingleton::getInstance();
    
 return 0;
}