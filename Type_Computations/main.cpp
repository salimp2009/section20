#include <iostream>
#include <type_traits>

// Example for Type Manipulations using Metaprogramming

// Remove Pointer Example
// just declare a struct (no need for definition)
template<typename T>
struct remove_pointer;          

// make specialization for remove pointer using T*
// define an alias using type = T; this removes the pointer from the type
template<typename T>
struct remove_pointer<T*> { using type = T;};    

// create an alias to make it easier to use the remove_pointer function that return T (type)
template<typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

// Alternative way for the remove_pointer Specialization and alias
// define a guide from remove_pointer(T*) that returns T
template<typename T>
auto remove_pointer_alt(T*)->T;

// Creating an alias using decltype and declval
// decltype evaluate the expression to get the type
// declval returns the type  as T&& and remove pointer uses T* specialization which returns T
template<typename T>
using remove_pointer_alt_t =decltype(remove_pointer_alt(std::declval<T>())); 

// Example for Remove Reference and create a Forward function 
//(from Visual Studio Developer Question; )
namespace Std {
    template <typename T> struct RemoveReference { using Type = T; };
    template <typename T> struct RemoveReference<T&> { using Type = T; };
    template <typename T> struct RemoveReference<T&&> { using Type = T; };
    template<typename T> using RemoveReference_t = typename RemoveReference<T>::Type;
    
    template <typename T> 
    T&& Forward(RemoveReference_t<T>& Arg)
   // T&& Forward(RemoveReference<T>::Type& Arg) 
    {
        return static_cast<T&&>(Arg);
    }
}

template <typename T> 
void Message(const T&) {}

template <typename Handler> 
void create(int buffer, Handler handler) 
{
    (void) handler;
    auto lambda = [buf = buffer]() mutable {
        Message(Std::Forward<decltype(buf)>(buf));
    };
    (void) lambda;
}

int main()
{
    create(11, 22);
    static_assert(std::is_same_v<remove_pointer_t<int*>, int>);
    static_assert(std::is_same_v<remove_pointer_alt_t<int*>, int>);

 
 return 0;
}