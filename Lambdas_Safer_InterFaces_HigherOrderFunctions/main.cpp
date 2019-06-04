#include <iostream>
#include <mutex>
#include <thread>
#include <future>


// classic way for a thread safe counter can expose safety issues
class threadsafe_counter
{
    std::mutex _mtx;
    int _value{0};
public:
    void add_one()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        _value+=1;
    }
    
    // not thread safe; forgot to lock
    void add_two()
    {
        _value+=2;
    }
};

// alternative implemantation of thread safe counter thru
// higher order function defined in a locked class
// to make sure that user can access the locked data and therefore it will be safer 
// for multithread operations; note normally the data should be atomic for a complete thread safe
// implementation 
template<typename T>
class Locked {
  std::mutex  _mtx;
  T _data;
public:
   Locked(int n): _mtx{}, _data{n} { }
  template<typename F>
  decltype(auto) access(F&& f);  // f will be access only it is locked
};

template<typename T>
template<typename F>
decltype(auto) Locked<T>::access(F&& f)  // access takes a function as an argument
{
    std::lock_guard<std::mutex> lock{_mtx};  // then we lock the data of the value which is a locked<int> type
    return std::forward<F>(f)(_data);        // we then pass data into f and return f function executed with data   
};

class threadsafe_counter_lambda
{
private:
  Locked<int> _value;
public:
  threadsafe_counter_lambda(int n): _value{n} { }
  int add_one();
  int add_two();
};

int threadsafe_counter_lambda::add_one()
{
    return _value.access([](int data){return data+=1;});
}

int threadsafe_counter_lambda::add_two()
{
   return  _value.access([](int data){return data+=2;});
}


int main()
{
    threadsafe_counter_lambda th{20};

//    auto fut=std::async(std::launch::async, &threadsafe_counter_lambda::add_one, &th );  // classic way to call a member function of a class
    auto fut1=std::async(std::launch::async, [&th]{ return th.add_one();} );
    auto fut2=std::async(std::launch::async, [&th]{ return th.add_two();} );
    
    auto sum = fut1.get() + fut2.get();
    
    std::cout<<"\nSum : "<<sum<<'\n';
    
 
 return 0;
}