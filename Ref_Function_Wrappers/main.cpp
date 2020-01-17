#include <iostream>
#include <functional>
#include <vector>

template<typename T>
void foo(T val)
{
    ++val;
    std::cout<<"value in foo(): "<<val<<'\n';
}

struct B
{
    B(int n):data{n} {}
    int data{0};
};

void funct(int x)
{
    std::cout<<"funct values: "<<x<<'\n';
}

class C
{
  public:
    void memfunct(int x) const
    {
        ++x;
        std::cout<<"Class member function increased value: "<<x<<'\n';
    }
};

// lamda return function that returns a lambda;
// std::function is used for the return type; 
// alternative way is to use 'auto' for return type
std::function<void(int)>lambda_return()
{
    return [](int x)
            {++x; std::cout<<"lambda from lambda_return increased value: "<<x<<'\n';};
}

int main()
{
    int x{5};
    foo(std::ref(x));           // any variable can be passed as a reference
                                // foo was defined to have argument by value
                                // std::ref() is a helper of function class std::reference_wrapper<>
    std::cout<<" value in main(): "<<x<<'\n';
    
    std::vector<std::reference_wrapper<B>>vecB;
    
    // Example for std::function<> ; function wrapper
    
    std::vector<std::function<void(int)>>tasks;
    tasks.push_back(foo<int>);                  // foo is template function the type info need while push_back
    tasks.push_back(funct);                     // funct is a regular function type info is in function definition
    tasks.push_back([](int x){std::cout<<"lambda values: "<<x<<'\n';});
    
    // passing values to functions in the vector
    for(auto f: tasks)
        f(33);
    // example for member functions; 
    std::function<void(const C&,int)>mem_f;         // when member functions are used the first argument inside paranthesis
    mem_f=&C::memfunct;                             // has to be the tpye of class, the remaining arguments are arguments the function takes 
    mem_f(C(), 5);                                  // outside the paranthesis we still have specifiy the return type as usual; 
                                                    // mem_f is a function_wrapper object with specified arguments
                                                    // class argument needs to be passed to create an object and
                                                    // and pass a value

    std::vector<std::function<void(const C&, int)>>vec_f;        // a vector taking function objects
    vec_f.push_back(&C::memfunct);                              // functions return void and takes a member function of the specified class
                                                                // when pushing_back, we specify the class member function that will be in the vector
    vec_f.at(0)(C(), 25);                                       // then we have to access the vector element and create an object of  that class //
                                                                // and pass a value that will be used for member function we specified 
                                                                        
    // function returning lamda example
    auto lambda_f=lambda_return();
    lambda_f(555);
    
    
    return 0;
}
