#include <iostream>

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
 
 double penny_saver(int n, double amount)
 {
     if(n<=1) return amount;
     //std::cout<<2*penny_saver(--n, amount)<<'\n';
     return 2*penny_saver(--n, amount);
 }

int main()
{
    std::cout<<factorial(30)<<'\n';
    std::cout<<fibonacci(30)<<'\n';
    std::cout<<penny_saver(18, 0.01)<<'\n';
    
    return 0;
}
