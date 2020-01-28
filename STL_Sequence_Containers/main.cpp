#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <numeric>
#include <iterator>
#include <deque>
#include <array>
#include <tuple>
#include <string>
#include <typeinfo>
#include <type_traits>

void STL_Array()
{
    std::cout<<"-------------------STL Array-------------------------\n";
    // default constructor does not create empty container
    // therefore for fundemantal types the initial value might be undefined
    // when nothing is passed to initialize;
    // alternative std::array<int, 5>x{}
    std::array<int, 5>arr1{1,3,5,7, 9};
    std::copy(arr1.begin(), arr1.end(),
            std::ostream_iterator<int>(std::cout, " "));
    
    
    std::array<int, 5>arr2{};
    std::cout<<'\n';
    for(const auto& elem:arr2)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    // Since C++17 automatic type and size deduction from arguments is OK
    std::array arr3{10,20,30,40};
    for(const auto& elem:arr3)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    std::cout<<"original addresses of arr1 elements: \n";
    for(const auto& elem:arr1)
        std::cout<<&elem<<" ";
    std::cout<<'\n';
    
    arr2=std::move(arr1);
     for(const auto& elem:arr2)
        std::cout<<elem<<" ";
    std::cout<<'\n';
    
    std::cout<<"addresseses of arr2 & arr1 elements after arr2=std::move(arr1):  \n";
    for(const auto& elem:arr2)          // the address of arr2 element are still same only values are changes
        std::cout<<&elem<<" ";
    std::cout<<'\n';
    
    for(const auto& elem:arr1)          // the addresses of arr1 elements are still valid
        std::cout<<&elem<<" ";
    std::cout<<'\n';
    
    arr1[2]=300;                        // direct access but no range check better to use .at() for range checnking
   // arr1.at(8);                       // runtime range checking ; throws exception
    std::cout<<arr1[8]<<'\n';           // no range cheking; not safe to use directly better to use with assert to check range             
    
    std::cout<<arr1[2]<<'\n';
    
    //std::get<>() helper function is defined in <array> but also it is in <iterator> as well
    std::cout<<std::get<2>(arr1)<<'\n';
    std::cout<<arr2.front()<<", "<<arr2.back()<<'\n';   
    // Note: The effect of calling front() or back() on a zero-sized array is undefined
    
    // std::array<> uses std::tuple<> interface so some of the commands can be used for arrays;
    // tuple_size<>::value, tuple_element<>::type and std::get<>
    
    typedef std::array<std::string, 5> String_Array;        // create an alias 
    
    String_Array arr4={"Salim", "Didem", "Demir", "Sema"};
    
    std::cout<<"std::tuple_size<>::value: "<<std::tuple_size<decltype(arr4)>::value<<'\n';
    
    std::cout<<typeid(std::tuple_element<1, String_Array>::type).name();
    
    std::cout<<'\n';
}

void STL_Vector()
{
    std::cout<<"-------------------STL Array-------------------------\n";
    std::vector<int>vec1(80, 20);               // creates a vector with 80 elements  with a value of 20   
    std::cout<<vec1.capacity()<<'\n';       // check number of elements with default allocator    
    vec1.reserve(100);
    std::cout<<vec1.capacity()<<'\n';       // return the number of elements that can be held 
    auto p=vec1.data();                      // data() return the underlying element for storage; 
                                            // it returns a pointer
    std::cout<<*p<<'\n';                    // print the first element similar to vec1[0]
    *p=50;                                  // change the value of first element
     *(p+1)=100;                            // access and change the 2nd element                            
    for(const auto& v:vec1)
        std::cout<<v<<" ";
    
    std::cout<<std::boolalpha<<std::is_pointer<decltype(p)>::value<<'\n';   // return true
    
    
    
    std::cout<<'\n';
}

void STL_Deque()
{
    std::cout<<"-------------------STL Array-------------------------\n";
    
}

void STL_List()
{
    std::cout<<"-------------------STL Array-------------------------\n";
    
}

void STL_Forward_List()
{
    std::cout<<"-------------------STL Array-------------------------\n";
    
}
int main()
{
   STL_Array();
//    STL_Vector();
//    STL_Deque();
//    STL_List();
//    STL_Forward_List();

    return 0;
}
