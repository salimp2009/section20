#include <iostream>
#include <type_traits>

// Example for Type_Traits in STL;
// Conjunction and Disconjunction;

// Conjunction: performing a logical AND on the sequence of traits
// Disjunction; performins a logical OR on the sequence of traits


// satify_all function used std:: conjunction that takes a variadic type of STL Traits
// and performs logical AND on the all passed type traits
template<typename T, template<typename>typename... Traits>
using satisfy_all = std::conjunction<Traits<T>...>;

// and performs logical OR on the all passed type traits
template<typename T, template<typename>typename... Traits>
using satisfy_any = std::disjunction<Traits<T>...>;

// Foo is a function that used enable_if to execute the body of function
// using satisfy_all to check if the type passed into foo function 
// satisfies all type traits; if it is a constant pointer and 
// if it does it prints otherwise compiler error will be displayed
template<typename T>
auto foo_all()->std::enable_if_t<satisfy_all<T, std::is_pointer, std::is_const>{}>
{
    std::cout<<"\nAll is satisfied "<<(std::is_pointer<T>::value && std::is_const<T>::value)<<'\n';
}

template<typename T>
auto foo_any()->std::enable_if_t<satisfy_any<T, std::is_pointer, std::is_const>{}>
{
    std::cout<<"\nAny satisfied; pointer or const: "
             <<(std::is_pointer<T>::value || std::is_const<T>::value)<<'\n';
}

int main()
{
   
    foo_all<int* const>();      // constant pointer ; all satisfied
   // foo_all<const* int>();    // compiler error pointer to constant; pointer is not constant 
    foo_any<int*>();            // Any is satisfied; pointer or const 

 return 0;
}