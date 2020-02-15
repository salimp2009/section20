#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <bitset>
#include <type_traits>

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
    friend std::ostream& operator<<(std::ostream& os, const B& obj) {
        return os<<obj.data<<'\n';
    }
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
std::function<void(int)> lambda_return()
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
    
    // using std::reference_wrapper so that vector can accept reference as a type info
    // std::vector<B&> does not compile so insteade we use reference_wrapper<> class
    // a better example to create a list type of container and use reference_wrapper
    // inside the vector so any changes to list effect the vector elements 
    std::vector<std::reference_wrapper<B>>vecB;
    B b(2);
    B* b_ptr=&b;
    b_ptr->data=333;
    std::cout<<" b.data: "<<b.data<<'\n';
    
    vecB.push_back(*b_ptr);
    for(auto elem:vecB)
        std::cout<<"vecB: "<<elem<<'\n';
    
    std::cout<<std::boolalpha<<std::is_same<B, decltype(vecB)>::value<<'\n';
    
    b_ptr=nullptr;
    delete b_ptr; // do not forget to delete your raw pointer :) ( better dont use it if you dont have too)
    
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
    
    // converting a string to bitset
    // the last two character identify where to place zeros and one 
    // with a given string composed of those characters
    // Full definition of the constructor for bitset<>
    // bitset(n == basic_string<CharT>::npos ? basic_string<CharT>(str) : 
    // basic_string<CharT>(str, n), 0, n, zero, one)
    // Simplified definition bitset<> constructor;
    // bitset(str, start_pos, number_of_characters, zero_character, one_character)
    
    std::string alpha_bit_string{"aaccaaacc"};
    std::bitset<10>b_string(alpha_bit_string, 2, 5, 'a', 'c');
    std::cout<<b_string<<'\n';
    
    alpha_bit_string = "aBaaBBaB";
    std::bitset<8> b6(alpha_bit_string, 0, alpha_bit_string.size(),
                      'a', 'B'); 
    
    std::cout<<b6<<'\n';
    return 0;
}
