#include <iostream>
#include <chrono>
#include <ratio>

// overload print operator to display the duration in terms of ticks and ratio of seconds
template<typename V, typename R>
std::ostream& operator<<(std::ostream& os, const std::chrono::duration<V,R>& dur)
{
    os<<"["<<dur.count()<<" ticks of "<<R::num<<"/"<<R::den<<" seconds]\n";
    return os;
}



int main()
{
    
    typedef std::ratio<5,3> Five_Thirds;                            // creating an alias for 5/3 ratio  by using typedef        
                                                        
    std::cout<<Five_Thirds::num<<"/"<<Five_Thirds::den<<'\n';       // num and den stands for numerator/denumerator of ratio
                                        
    std::ratio<42, 42> one;
    std::cout<<one.num<<"/"<<one.den<<'\n';
    
    std::ratio<0>zero;
    std::cout<<zero.num<<"/"<<zero.den<<'\n';
    
    using Alt_Five_Thirds=std::ratio<25,15>;
    std::cout<<Alt_Five_Thirds::num<<"/"<<Alt_Five_Thirds::den<<'\n';       // the output is 5/3

    Alt_Five_Thirds five_thirds_object;                                     // creating an object of type Alt_Five_Thirds
    std::cout<<five_thirds_object.num<<"/"<<five_thirds_object.den<<'\n';   // which is actually ratio<5, 3>
    
    typedef std::ratio<7, -3>Neg;
    std::cout<<Neg::num<<'/'<<"/"<<Neg::den<<'\n';                          // output is -7/3
    
    // duration is the number of ticks in seconds
    // duration<tick, a fraction of unit in seconds>
    // duration type gets two type info; the first one is type of the number ticks
    // second one is a fraction of seconds ; default value is seconds
    // for the second one ratio is used to specify a specific fraction
    
    // seconds
    std::chrono::duration<int>twenty_seconds(20);       
    // duration<int> indicates a second and the object gets an argument
    // which represent the number of ticks; so 20 stands for 20 seconds
    
    
    // minutes
    std::chrono::duration<double, std::ratio<60>>half_minute(0.5);      
    // here the duration is 60 seconds because ratio is specified as ratio<60>
    // duration gets a double because we want to create an object of half minute so 
    // the argument for the object is 0.5 which half of 60 seconds=half minute
    
    // milliseconds
    std::chrono::duration<long, std::ratio<1, 1000>>one_millisecond(1);
    // here the duration is 1/1000 seconds which is milliseconds
    // the type is specified as long because we want 1 millisecond
    
    std::cout<<twenty_seconds.count()<<" seconds"<<'\n';            // count will give the tick of an duration object;
    std::cout<<half_minute.count()<<" minutes"<<'\n';
    std::cout<<one_millisecond.count()<<" milli seconds"<<'\n';
    
    std::cout<<" twenty_seconds + half_minute is: "<<(twenty_seconds +half_minute).count()<<" seconds\n";
    
    // example chrono_literals
    using namespace std::chrono_literals;
    auto day=24h;
    std::cout<<day.count()<<" hours\n";
                                                        
    // std::chrono has set types;
    // std::chrono::seconds
    // std::chrono::hours
    // std::milliseconds
    
    std::chrono::seconds d1(42);                        // 42 seconds
    std::chrono::milliseconds d2(10);                   // 10 milliseconds
    
    std::cout<<(d1+d2).count()<<'\n';                   // 42010 milliseconds
    std::cout<<(d1-d2).count()<<'\n';                   // 41990 milliseconds
    
    std::chrono::duration<int, std::ratio<1,3>>d3(1);   // 1 tick of 1/3 second
    std::chrono::duration<int, std::ratio<1,5>>d4(1);    // 1 tick of 1/5 second
    
    std::cout<<d3<<" + "<<d4<<"= "<<d3+d4<<'\n';
    return 0;
}
