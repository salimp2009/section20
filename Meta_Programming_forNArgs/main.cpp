#include <iostream>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <vector>
#include <tuple>
#include <unordered_map>

// forNArgs will create an Index Sequence passed to a function in groups
// of N during compile time 
// the difference between for_each_args is the total index sequence will be passed
// in groups of N ; it does it during compile time and the N will be passed as template
// parameter by the user

template<typename, typename>
struct forNArgsImpl;

template<std::size_t TArity, typename TF, typename... Ts>
void forNArgs(TF&& mFn, Ts... mXs) 
{   // mfn is the function that will be  passed, mXs are the passed arguments
    // total number of Arguments
    constexpr auto numberOfArgs(sizeof...(Ts));
    
    // the number of arguments passed must be divisible by N
    static_assert(numberOfArgs % TArity==0, "Invalid number of arguments");
    
    // call a specliazed version implementation file of forNArgsImpl
    // that was forward declared
    forNArgsImpl<std::make_index_sequence<numberOfArgs/TArity>,       // this will determine the number of function calls
                 std::make_index_sequence<TArity>>
    ::exec(mFn, std::forward_as_tuple(std::forward<Ts>(mXs)...));     // exec will be defined later as a static function; 
                                                                      // pass the function and forward the arguments as tuple
} 
    // Specilization of the implementation function
    template<std::size_t... TNCalls, std::size_t... TNArity>
    struct forNArgsImpl<std::index_sequence<TNCalls...>, std::index_sequence<TNArity...>>
{
    template<typename Tf, typename... Ts>
    static void exec(Tf&& mFn, const std::tuple<Ts...>& mXs)    // static function definition
    {   
        constexpr auto arity(sizeof...(TNArity));              // calculate the the Arity again               
        // instead of using std::initiliazer list
        // an array of bools will be used to expand the parameters
        using swallow=bool[];
        
        // implementation of swallow similar to initiliazer list
        // return type void is used and inside the swall we use paranthesis and comma operator
        // inside the paranthesis we will write the expression we want to evaluated
        // and after the comma we will pass a boolean value since the array is bool type
        (void) swallow{(execN<TNCalls * arity>(mFn, mXs), true)...}; 

    }
    
    template<typename std::size_t TNBase, typename Tf, typename... Ts>
    static void execN(Tf&& mFn, const std::tuple<Ts...>& mXs) {
    
        return mFn(std::get<TNBase+TNArity>(mXs)...);
    }
};


// Example for make_unordered_map
// it take N number of arguments and return unordered_map
// N number of arguments will be forwarded as groups of
// first agument of each group will be Key
// second argument of each group will be Value

template<typename... TArgs>
auto make_unordered_map(TArgs&&... mArgs);

// first create a helper function function to deduce 
// the common type for all keys and common type for all Values

// every even element will be keys   0  2  4  6  8...
// every ood  element wiii be value    1 3  5  7  9...      

// helper function single type TSeq for index sequence
// index_sequence will start from 0 to sizeof... (Ts)/2 
// index_sequence 
template<typename TSeq, typename... Ts>          
struct CommonKVHelper;              // KV stands for Key Value

// specialized CommonKVHelper; // TIs stands for Index type

template<std::size_t...TIs, typename... Ts>
struct CommonKVHelper<std::index_sequence<TIs...>, Ts...>
{
  static_assert(sizeof...(Ts)%2==0, "");  
  
  // in order to determine the type of values at specific Indexes 
  // use std::tuple_element<I, std::tuple<Ts...>>
  // gives the type of element at Index I 
  // that way determine the type of Key and Values
  template<std::size_t TI>
  using TypeAt=std::tuple_element_t<TI, std::tuple<Ts...>>;
  
  // get the types of the Keys every even Index no (0 2 4 6 8..)
  
  using KeyType=std::common_type_t<TypeAt<TIs*2>...>;      // Note ... is needed since we need Key type at 0 2 4 6...
 
 // types of value at odd Index TI*2+1 (1 3 5 7 .....)   
    using ValueType=std::common_type_t<TypeAt<(TIs*2) + 1>...>;
};

// Additional helpers to created Ts/2 index sequence

template<typename... Ts>
using HelperFor=CommonKVHelper<std::make_index_sequence<sizeof... (Ts)/2>, Ts...>;

template<typename... Ts>
using CommonKeyType=typename HelperFor<Ts...>::KeyType;

template<typename... Ts>
using CommonValueType=typename HelperFor<Ts...>::ValueType;

// Check if the helper function gives correct result
static_assert(std::is_same<CommonKeyType<std::string, int>, std::string>(), "");   // KeyType should be std::string

static_assert(std::is_same<CommonValueType<std::string, int>, int>(), "");         // ValueType should be int

// Check with more data; if the helper function gives correct result
static_assert(std::is_same_v<CommonKeyType<std::string, int, std::string, float, const char*, long>,  // Key, Value, Key, Value,...  
                                           std::string>, "");                                        // KeyType should be std::string

// Check with more data; if the helper function gives correct result
static_assert(std::is_same_v<CommonValueType<std::string, int, std::string, float, const char*, long>,  // Key, Value, Key, Value,... 
                                           float>, "");                                          // Value Type should be float
                                           
// implemantation make_unorder_map function
template<typename... TArgs>
auto make_unordered_map(TArgs&&... mArgs)
{
  // create Key and Value types
  using KeyType=CommonKeyType<TArgs...>;  
  using ValueType=CommonValueType<TArgs...>;
  
  std::unordered_map<KeyType, ValueType>result;
  result.reserve(sizeof...(TArgs)/2);
  
  forNArgs<2>([&result](auto&& key, auto&& value) { result.emplace(std::forward<decltype(key)>(key), std::forward<decltype(value)>(value));}, 
                std::forward<TArgs>(mArgs)...);
    
   return result; 
}



int main()
{
    // test for make_unordered_map function
    
    using namespace std::literals;
    
    auto m =make_unordered_map("zeros"s, 0, "one"s, 1, "two"s, 2.f);          // "zeros"s is a std::literal that makes std::string("zero")
    
    static_assert(std::is_same_v<decltype(m), std::unordered_map<std::string, float>>, "");
    
    std::cout<<m["zero"]<<", "<<m["one"]<<", "<<m["two"]<<'\n';
    
    std::cout<<'\n';
    
    
    // forNArgs basically passes arguments into a function in groups
    // which define as the template parameter of forNArgs
    // in the below example the data will be passed lambda function with two groups
    // we have 4 arguments so on each function call 2 of them will be called
    // which also matches the input number of arguments of the lambda
    forNArgs<2>([](auto&& x, auto&& y) { std::cout<<x+y<<'\n';},
                   10,20,30,40
    );
    
     int num{5};
     auto add5=[num](auto&& x, auto&& y) { std::cout<<x+y+num<<'\n';};
     forNArgs<2>(add5,10,20,30,40);

    return 0;
}
