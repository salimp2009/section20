#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>



// Basic Examples for Recursive Functions
 unsigned long long factorial(unsigned long long  n)
{   
    if(n==0 || n==1) 
        return 1;
    else
        return n*factorial(n-1);
}

 unsigned long long fibonacci(unsigned long long  n)
 {
     if(n<=1) 
         return n;
    return fibonacci(n-1)+fibonacci(n-2);
 }
 
// Example for saving some pennies every day;
// everyday savings is double the amount of previous day
 double penny_saver(int n, double amount)
 {
     if(n<=1) return amount;
     return penny_saver(--n, 2*amount);
 }
 
 int test_rvalue(const int &n)
 {
     return n*n;
 }

int main()
{
    test_rvalue(5);
    
    int scores[]{10,20,40,50};
    for(auto i: scores)
        std::cout<<i<<'\n';
     std::cout<<"---------------------------------------------\n";
     
    int *ptr{scores};
    int **ptr_ptr{&ptr};
    int **ptr2 = new int*;
    
    int *ptr3=new int;
    *ptr3=20;
    
    *ptr2=ptr3;
    
    std::cout<<&ptr3<<", "<<ptr3<<", "<<*ptr3<<'\n';
    std::cout<<&ptr2<<", "<<ptr2<<", "<<*ptr2<<", "<<**ptr2<<'\n';
    
    
    std::cout<<"address of scores array: "<<scores<<'\n';
    std::cout<<"Value of pointer ptr (address of scores): "<<ptr<<'\n';
    std::cout<<"Value of pointer to pointer: "<<*ptr_ptr<<'\n';
    
    std::cout<<"---------------------------------------------\n";
    std::cout<<"\nsecond element of scores[1]: "<<scores[1]<<" or "<<*(scores+1)<<'\n';
    std::cout<<"\nsecond elem thru pointer ptr: "<<*(ptr+1)<<'\n';
    std::cout<<"\nsecond elem thru pointr to pointr ptr_ptr: "<<*(*ptr_ptr+1)<<'\n';
    
    // the address of pointer is incremented by n*sizeof(type)
    // ptr+n; n is the increment amount 
    std::cout<<"---------------------------------------------\n";
    std::cout<<"second elem address thru pointer ptr: "<<ptr+1<<'\n';
    std::cout<<"third elem address thru pointer ptr: "<<ptr+2<<'\n';
    std::cout<<"fourth elem address thru pointer ptr: "<<ptr+3<<'\n';
    
    // using C-style arrays in STL algorithms
    std::cout<<"---------------------------------------------\n";
    std::for_each(std::begin(scores), std::end(scores),
            [](auto n){ std::cout<<n<<", ";});
    std::cout<<'\n';
    
    std::cout<<"\n---------------Type Trait std::extent<>------------------\n";
    std::cout<<"Determining the size of array using type traits: "
                <<std::extent<decltype(scores)>::value<<'\n';
                
    // Example of std::rank and std::extent type traits; gives info about array dimensions and types
    //std::rank<>::value gives the dimension of an array;e.g. int array[][]; it gives 2
    
    // std::extent<>::value gives the number of elements; if it is a multidimensional array 
    // the dimension should be passed with the type info; std::extent<int[5][7], 1>::value gives 7
    
    // remove_extent<>::type gives the type info of the one f the extent ; it gives the type info
    // it does not really give delete data only provides type and access 
    std::copy(scores, scores+(std::extent<decltype(scores)>::value), 
            std::ostream_iterator<typename std::remove_extent<decltype(scores)>::type>(std::cout, " ") );
    
    // std::size() is a utility function since C++17 and can check raw array sizes
    // include <iterator> library
    std::cout<<"\nstd::size: "<<std::size(scores)<<'\n';
    
    std::cout<<"\n----------------Recursive Function Examples---------------\n";
    std::cout<<"factorial: "<<factorial(30)<<'\n';
    std::cout<<"fibonacci: "<<fibonacci(30)<<'\n';
    std::cout<<"penny_saver: "<<penny_saver(18, 0.01)<<'\n';
    std::cout<<"---------------------------------------------\n";
    
    return 0;
}
