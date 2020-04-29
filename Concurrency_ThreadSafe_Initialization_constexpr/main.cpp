#include <iostream>
#include <thread>
#include <future>

class MyDouble{
    private:
        double val1;
        double val2;
    public:
        constexpr MyDouble(double v1, double v2): val1{v1}, val2{v2} { }
        constexpr double getSum() const { return val1+val2;}
};

template<typename T>
constexpr auto sumUp(const T x, const T y)
{
    
    double sumTotal=x+y;
    return sumTotal;
}

int main()
{
    constexpr double myStatVal=2.0;
    constexpr MyDouble myStatic{10.5, myStatVal};
    constexpr auto sumStat=myStatic.getSum();
    static_assert(sumStat==12.5);
    
    constexpr auto total=sumUp(sumStat,myStatVal);
    
    static_assert(total==sumStat+myStatVal);
    
    std::cout<<"total= "<<total<<'\n';
    
    auto fut1= std::async(std::launch::async, [&](){ return myStatVal + myStatic.getSum();});
    auto fut2= std::async(std::launch::async, [&]() { return sumUp(sumStat,myStatVal);});
    
    auto total1=fut1.get()+fut2.get();
    
    std::cout<<"total1= "<<total1<<'\n';
    
    return 0;
}
