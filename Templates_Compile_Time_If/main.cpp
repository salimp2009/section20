#include <iostream>
#include <functional>
#include <type_traits>
#include <string>
#include <vector>


template<typename... TArgs>
decltype(auto) sum2(TArgs...args)
{
    if constexpr ((std::is_integral_v<TArgs> && ...)) {
            std::cout<<std::boolalpha<<"integer: ";
            return (args+ ...);
            
    } else if constexpr ((std::is_floating_point_v<TArgs> || ...)) {
            std::cout<<"floating point: ";
            return (args+ ...);
            
    } else {
        std::cout<<"not an integral or floating point= ";
        return (args+ ...);
    }
}

template<typename T>
auto asString(T x) 
{
    if constexpr(std::is_same_v<T, std::string>)    // if a runtime if () is used it gives compiler error
        return x;                                   // because templates are compiled as a whole even if the first
    else if constexpr(std::is_arithmetic_v<T>)      // condition becomes false, the statement after that should be correct   
        return std::to_string(x);                   // if constexpr is used the false statement is discarded
                                                    // but if we use regular runtime if then statement is not discarded and
    else                                            // if the statement after is not compilable then it gives an compile error
                                                    // even the true case is OK, it generates error because the statement after the false branch
        return std::string(x);                      // is not compilable; this does not happen with if constexpr since the false branch will be
}                                                   // discarded during first phase of compilation of templates (templates are compiled in two stages) 

template<typename T>
constexpr auto foo(const T& val)
{
    
    if constexpr (std::is_integral<T>::value) // both return statements compiles because the both values  are valid
   // if constexpr (std::is_integral<T>::value && T{} <10)
    {
        if constexpr (T{} < 10) return val*2;
    }
    return val;
}


int   add(int x, int y)     {return x+y;}
float add(float x, float y) {return x+y;}

struct  S 
{
    int8_t a:3=0;       // this initialization is a C++20 option but compiles with C++17 with a warning that is C++20 extension
    int8_t b:5=0;
};

//simple macro example that takes a variable and prints it
// macros should be mostly used for stripping out code that should not be in release mode



//#ifdef PR_DEBUG                 // PR_DEBUG is used only debug build
#if PR_DEBUG==1                   // a better wayto define a macro instead of #ifdef; 
                                  //if the value is replaced with 0 the code will work in release mode                  
    #define LOG(x) std::cout<<"Macro works: "<<x<<'\n'
#elif defined(PR_RELEASE)                   
    #define LOG(x)               // used in release mode 
#endif

// for an example of std::function
// std::function is not a zero cost abstraction
// if the object is big then dynamic allocation might be needed; not for small ones
// hard to inline for compilers
// try to avoid; use lambda and perforwarding or auto& to lambda
class C 
{
public:
    int m;
    C()=default;
    C(int data): m{data} {}
    void memfunc(int x, int y) const { std::cout<<"class C memfunc; x+y= "<<x+y<<'\n';}
};

struct button
{
    std::vector<std::function<void()>>on_click;  
};

void open_model(int n)
{
    std::cout<<"opening model: "<<n<<'\n';
}

int main()
{
    button b;
    b+=
    b.on_click.emplace_back(+[]{ open_model(1);});                      // + unary operator in front of a lambda turns the lambda 
    b.on_click.emplace_back(+[] { std::cout<<"opening model...\n";});  // into function pointer as long as it do it does not capture anything
    
    b.on_click[0]();    // get the function pointer from the container(std::vector) and instantiate
    b.on_click[1]();    // get the next element in the container and instantiate
    
    // an example of std::function
    std::function<void(const C&, int, int)>funct_ptr=&C::memfunc;
    funct_ptr(C{}, 5, 4);
    
    std::function<int(C const&)>funct_ptr2=&C::m;
    C c1(20);
    std::cout<<"func_ptr2= "<<funct_ptr2(c1)<<'\n';         // passing a reference to an existing instance of C
    std::cout<<"func_ptr2= "<<funct_ptr2(C{25})<<'\n';      // passing temporary instance with a value and access member data
    
    
    std::cout<<"size of S: "<<sizeof (S)<<'\n';
    
    constexpr auto x1=foo(42);          // both compiles because the both conditions of foo is valid 
    constexpr auto x2=foo("hello");
    
    std::cout<<"x1: "<<x1<<", x2: "<<x2<<'\n';
    
    asString(42);
    
    std::cout<<"sum2: "<<sum2(3, 3.2)<<'\n';
    std::cout<<"sum2: "<<sum2(4, true)<<'\n';
    std::cout<<"sum2: "<<sum2(std::string("42"), std::string("salim"))<<'\n';
    
    // example for lambda to work with overloads with auto deduce
    // since the add function has two overloads, the compiler needs to know which one will be used since
    // x can be float or int depending on runtime therefore static_cast is used so that both argument are iether float or int
    auto add10=[](auto x){ return add(static_cast<decltype(x)>(10), x); };  
    
    std::cout<<"add10(20)= "<<add10(20)<<'\n';
    
    LOG(add10(25));

    return 0;
}