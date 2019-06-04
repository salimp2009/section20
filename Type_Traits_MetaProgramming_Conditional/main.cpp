#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>

template<typename T>
struct items
{
  std::vector<T>_data;  
};

// Alternative struct to pass reference into a vector 
// conditional_t allows us to check the type of the object for a given predicate
// and allows to define true and false cases
template<typename T>
struct item_alt 
{
    using item_type =std::conditional_t<                        // create an alias for item_type using conditional_t type traits
    std::is_reference_v<T>,                                     // if T is a reference type
    std::reference_wrapper<std::remove_reference_t<T>>, T>;     // if true remove the reference from then use reference wrapper
                                                                // if false passed T will be used as it is
    std::vector<item_type>_data;                                // use the item_type alias for the vector type;
};  

int main()
{
    items<int>i0;                                   // compiles OK
   // items<int&>iref;                              // compiler error; use a reference wrapper or 
                                                    // use conditional and reference_warpper while definining the struct
    items<std::reference_wrapper<int>>i1;           // any reference to int can be passed into vector     
    items<int*>i2;                                  // compiles OK; pointers are OK
    
    item_alt<int&>i_alt0;                           // compiles OK
 
 return 0;
}