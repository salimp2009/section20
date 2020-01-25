#include <iostream>
#include <algorithm>
#include <functional>



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

int main()
{
    int scores[]{10,20,40,50};
    for(auto i: scores)
        std::cout<<i<<'\n';
     std::cout<<"---------------------------------------------\n";
     
    int *ptr{scores};
    int **ptr_ptr{&ptr};
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
    std::cout<<"---------------------------------------------\n";
    
    std::cout<<"factorial: "<<factorial(30)<<'\n';
    std::cout<<"fibonacci: "<<fibonacci(30)<<'\n';
    std::cout<<"penny_saver: "<<penny_saver(18, 0.01)<<'\n';
    std::cout<<"---------------------------------------------\n";
    
    return 0;
}
