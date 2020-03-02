#include <iostream>
#include "Utility.hpp"
#include <cstring>
#include <charconv>

// Function Object 
template<typename T>
class AddValue {
  private:
    T value;            // value to be added
public:
    AddValue(T val):value{std::move(val)} { }

void operator()(T& elem) const {    // elem is the element that will be passed by algorithm
    elem+=value;                    // since the elem is passed by reference its value will change
} 
};

int main()
{
    std::vector<int>vec1{1,3,5,7,8,9,13,45,67};
    display(vec1);
    
    std::for_each(vec1.begin(), vec1.end(), 
                [](const int elem){std::cout<<elem*elem<<'\n';});
    
    // add the value of the 1st element to each value
    // capture [=] the value of first element (vec1.begin() into lambda by value then 
    // it is the same effect adding a const value
    std::for_each(vec1.begin(), vec1.end(), 
                [=](int& elem){ elem+=*vec1.begin();});
    display(vec1);
    
    // if we capture vec1.begin() by reference than the value added to other elements will
    // be different since the value of the first element will be changed as well
      std::for_each(vec1.begin(), vec1.end(), 
                [&](int& elem){elem+=*vec1.begin();});
    display(vec1);
    
    std::for_each(vec1.begin(), vec1.end(), AddValue<int>(25));
    display(vec1);
    
    std::for_each(vec1.begin(), vec1.end(), AddValue<int>(*vec1.begin()) );
    display(vec1);
    
    std::vector<int>vec2;
    
    std::transform(vec1.begin(), vec1.end(),          // source range
                   vec1.begin(),                     // if the destination is same with source no need for insertion
                   [](int elem){ return elem+3;});
    display(vec1);
    
    std::transform(vec1.begin(), vec1.end(),          // source range
                   std::back_inserter(vec2),          // insert into destination range; if the destination has no elements 
                   [](int elem){ return elem+3;} );   // we have to use inserter; if the dest container has same amount elements no need for inserter
                                                      // elem from source is added 10 and copied 
                                                      // into destination; if the destination is same with source
                                                        // then the value of source will be changed
    //display(vec1);
    display(vec2);
    
    std::vector<int>vec3{1,2,3,4,3,6,3,8};
    display(vec3);
    
    double meanvalue{0.0};::
    // using lambda to calculate the mean value
    std::for_each(vec1.begin(), vec1.end(),
                        [num=0l, sum=0l, &meanvalue](const int& elem)mutable{                   // lambda has two internal variables initialized
                            num++; sum+=elem;                                                   // in the capture list and used at every iteration to store sum
                            meanvalue=static_cast<double>(sum)/static_cast<double>(num);});     // lambda also captures meanvalue by reference and store
                                            
    std::cout<<meanvalue<<'\n';
    display(vec3);
    
    // counts the number of given value
    auto num=std::count(vec3.begin(), vec3.end(), 3 );
    std::cout<<num<<'\n';
    
    // counts the elements that satisfy the predicate; e.g. even numbers in the below example 
    auto num1=std::count_if(vec3.begin(), vec3.end(), [](const auto& elem){ return elem%2==0;});
     std::cout<<num1<<'\n';
     
     // minmax_element return the position the min and max element as a pair
     // max_element, min_element returns the positions of max and min elements respectively
     auto[min, max]=std::minmax_element(vec2.begin(), vec2.end());
     std::cout<<"min: "<<*min<<", max: "<<*max<<'\n';
     std::cout<<"distance min-max: "<<std::distance(min, max)<<'\n';
     display(vec2);
     
     auto[mmin, mmax]=std::minmax_element(vec1.begin(), vec1.end(), 
                        [](const auto& x, const auto& y){ return x<y;});
                        
    std::cout<<"mmin: "<<*mmin<<", mmax: "<<*mmax<<'\n';
    display(vec1);
     
    // find, find_if algorithms find the first matching element and returns the position
    // if the ranges are sorted using binary_search, lower_bound, upper bound algorithms recommended for performance
    
    auto pos3=std::find_if(vec2.begin(), vec2.end(), [](const auto& x){ return x%3==0;}); 
    if(pos3!=vec2.end())
        std::cout<<*pos3<<'\n';
        
    const char *st="12 monkeys got crazy 455";
    int value{0};
    
    // std::from_chars() converts a given character sequence into a numeric value
    // it returns a struct that has two element const char* p and std::err ec (for error checking)
    // the example goes thru c-string st and finds the numeric 12 and stores in the passed value
    // this is more efficient than using string stream (uses too much resources)
    // but if there are more than one numeric value, it returns the first one
    // ptr stores should store the position of the first match 
    // need more examples ???
    if(auto[ptr, ec]=std::from_chars(st, st+std::strlen(st), value); ec==std::errc{}) 
        std::cout<<value<<", ptr: "<<ptr<<'\n';
    
    return 0;
}
