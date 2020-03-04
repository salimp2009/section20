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
        
    const char *st="45.56";
    int value{0};
  //  const auto format=std::chars_format::general;   // if floating point value is used the format has to be explicit
 
    
    // std::from_chars() converts a given character sequence into a numeric value
    // it returns a struct that has two element const char* p and std::err ec (for error checking)
    // the example goes thru c-string st and finds the numeric value and stores in the passed value
    // this is more efficient than using string stream (uses too much resources)
    // but if there are more than one numeric value, it returns the first one
    // ptr refers to the first character not parsed as part of the number 
    // if the string start with characters then parsing stops so the numeric value has to come first
    // e.g.; "monekys455" gives no result but "455monkey" will give value 455
    // ec is initialized if the parsing is successfull, if not it is null
    // therefore ec==std::errc{} indicates parsing is OK
    
    if(auto[ptr, ec]=std::from_chars(st, st+std::strlen(st), value); ec==std::errc{}) 
        std::cout<<value<<", ptr: "<<ptr<<'\n';
        
        
//     if(auto[ptr, ec]=std::from_chars(st, st+std::strlen(st), value); ec==std::errc{}) 
//        std::cout<<value<<", ptr: "<<ptr<<'\n';


    // a counter version std::to_chars is also available
    // std::to_chars() converts numeric values into a given character sequence
    // stores the numeric value as a char without converting it to ASCII character
    // it works in the reverse of from_chars
    // it stores the passed numeric value into the passed string variable
    // when displayed it will show the same numeric value but the type will be char
    
    int new_value{14500999};
    char str[10];
    
    std::to_chars_result result=std::to_chars(str, str+10, new_value);
    *result.ptr='\0'; // to make sure the resulting has the end of c-string by '\0'
    
    std::cout<<str<<'\n';       // displays 90 but the type is char
    
    // search for n consecutive element that is equal to a value; returns position of first matching cond
    // example searchs for 2 consecutive of elements that are equal to 3
    
     std::vector<int>vec4{1,1,1,2,2,3,3,4,4,4,3,3,36,3,8};
    display(vec4);
    
    auto pos4=std::search_n(vec4.begin(), vec4.end(), 2, 3);
    if(pos4!=vec4.end())
        std::cout<<std::distance(vec4.begin(), pos4)+1<<" element"<<'\n'; 
    
    // 3 consecutive elements with the value of 0 and even number 
    // the value has to be passed into predicate but the predicate condition
    // will overwrite; if the value does not match but predicate is true then 
    // predicate will override 
    auto pos5=std::search_n(vec4.begin(), vec4.end(), 3, 3, 
                            [](const auto& elem, auto value){ return elem%2==0; });
    if(pos5!=vec4.end())
        std::cout<<std::distance(vec4.begin(), pos5)+1<<" element"<<'\n'; 
        
    // auto type deduction from the initialization C++17 feature
    // std::vector<int> deduced in the below example
    std::vector vec5 {1,2,3,4,5,6,7,3,4,5,6,13,15,25,33,45};
    std::vector vecsub {3,4,5,6};
   
    // search for a matching subrange of elements and return the position of the first matching
    // element of subrange
    auto pos6 = std::search(vec5.begin(), vec5.end(), vecsub.begin(), vecsub.end());
    display(vec5);
    display(vecsub);
    
    // print the matching pos and continue to search if there are more matching subranges
    while(pos6!=vec5.end()) 
    {
        std::cout<<"subrange found at pos: "<<std::distance(vec5.begin(), pos6)+1<<'\n';
        ++pos6;
        pos6=std::search(pos6, vec5.end(), vecsub.begin(), vecsub.end() );
    } 
    
    //  subrange to check consequetive elements of even, odd, even
    std::array<bool, 3>checkevenodd {true, false, true};
    display(checkevenodd);
    
    auto searchLamda=[](auto elem, bool subelem){                   // check range to match the subrange criteria; if
                            if(subelem)                             // if sub elemen is true(means check for even)
                                return elem%2==0;                   // check elem (from range) is even number 
                            else                                    // if subelem is false (means check for odd)
                                return elem%2==1;                   // check if elem (from range) is odd
                            };
    
    auto pos7=std::search(vec5.begin(), vec5.end(),                 // range
                         checkevenodd.begin(), checkevenodd.end(),  // subrange; even or odd criteria; if true it is even, otherwise odd
                         searchLamda);                             // search criteria
    
    std::cout<<"match found at pos: "<<std::distance(vec5.begin(), pos7)+1<<'\n';
    
      while(pos7!=vec5.end()) 
    {
        // print the first match
        std::cout<<"subrange found at pos: "<<std::distance(vec5.begin(), pos7)+1<<'\n';
        
        // continue to search from the next element; the start pos is incremented 
        // for the next search inside the search algorithms ++pos7
        // previous example ++pos7 was outside ; it is the same 
        pos7=std::search(++pos7, vec5.end(),
                             checkevenodd.begin(), checkevenodd.end(),  
                             searchLamda);       
    } 
    
     // search last subrange;
     // std::fin_end starts searching from the end; it can be used backwards searching
    
    //first search; starts from the end
    auto pos8 = std::find_end(vec5.begin(), vec5.end(), vecsub.begin(), vecsub.end());  
    
    // to continue searching we need a while loop and new end
    std::vector<int>::iterator end(vec5.end());
    while(pos8!=end) {
        std::cout<<"found subrange at position: "<<std::distance(vec5.begin(), pos8)+1<<'\n';
        
        // set the new end from the previous search so we search the remainder
        end=pos8;
        // if the search cannot find, it will return the position of end
        // and that will terminate the loop otherwise it will find new position
        // and will make a new search but the end will change by the expression; end=pos8
        pos8 = std::find_end(vec5.begin(), end, vecsub.begin(), vecsub.end()); 
    }
    
    // Search First of Several Possible elements
    // in this search if the element match any of the elements in the search range 
    // it return the position the first match
    // if there is no match, it returns the end
    // if a predicate is passed op(elem, searchElem) will search the whole search range and return true 
    // if there is a match e.g. [](elem, searchElem){ return elem==searchElem;}
    
    std::vector vec6 {1,2,3,4,5,6,7,8,9,10,11};
    std::vector vecsub2 {4,5,2};
    
    auto pos9=std::find_first_of(vec6.begin(), vec6.end(), vecsub2.begin(), vecsub2.end());
    std::cout<<"finding first match at position: "<<std::distance(vec6.begin(), pos9)+1<<'\n'; // return position 2 because 
                                                                                               // it matches one of the elements of search range
    
    // search if any of element is equal two times of the any element in search range
    auto pos9a=std::find_first_of(vec6.begin(), vec6.end(), vecsub2.begin(), vecsub2.end(),
                                [](const auto& elem, const auto& searchElem){return elem==searchElem*2;});
    std::cout<<"finding first lambda match at position: "<<std::distance(vec6.begin(), pos9a)+1<<'\n';   // same as previous example
    
    return 0;
}
