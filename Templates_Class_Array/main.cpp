#include <iostream>
#include "MyArray.hpp"



int main()
{
    MyArray<int, 5> arr1{20, 30, 40, 50, 60};
    std::cout<<arr1<<'\n';
    
    MyArray<int, 5> arr2{20};
    std::cout<<arr2<<'\n';
    
    MyArray<int, 5> arr3{arr2};
    std::cout<<"my arr3: "<<arr3<<'\n';
    
    std::cout<<"size: "<<arr3.size()<<'\n';
    
    arr3.fill(55);
    std::cout<<"arr3 revised: "<<arr3<<'\n';
    std::cout<<"arr2 after arr3 revised: "<<arr2<<'\n';
    
    std::cout<<"arr1 fist elem: "<<arr1[0]<<'\n';
    std::cout<<"arr1 remaining elems: "<<arr1[1]<<","<<arr1[2]<<","<<arr1[3]<<'\n';
    
   // std::cout<<"checking out of range access: "<<arr1[5]<<'\n';           // out of range error in DEBUG mode; 
                                                                            // but no error checking in release mode

    MyArray<std::string, 20> stringArr{"salim", "didem", "sema", "demir", std::string{"semsi"}};
    std::cout<<stringArr<<'\n';
    
    std::cout<<std::boolalpha;
    
    // checking if the types are std::string not const char*
    // using is_same<type1, type2>()   // note () is needed to generate ::value (1 or 0, true or false)
    std::cout<<std::is_same<decltype(stringArr), decltype(MyArray<std::string, 20>{})>()<<'\n';  // true
     
    // check for const char* using is_same_v<type1, type2>
    // note the () at the end is not needed since _v version generates is_same<>::value
    std::cout<<std::is_same_v<decltype(stringArr), decltype(MyArray<const char*, 20>{})><<'\n';  // false

    // checking the typedef of the class is working value_type, size_type defined
    std::cout<<std::is_same_v<MyArray<std::string, 20>::value_type, std::string><<'\n';
    
    // alternative way of checking inter type of an object using typedefs of the class
    std::cout<<std::is_same_v<decltype(stringArr)::value_type, std::string><<'\n';
    
    return 0;
}
