#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

void display(const std::array<int,5>& arr) {
    std::cout<<"\n[";
    for(const auto& a:arr)
        std::cout<<a<<" ";
    std::cout<<"]\n";
}

void test1() {
    std::cout<<"\n==========Test 1==============\n";
    std::array<int,5>arr1{1,2,3,4,5};    // double {{}} needed if C++11
    std::array<int,5>arr2{};            // if {} are not used than 
                                        //elements are not initialized; cwill ontain garbage
    
    display(arr1);
    display(arr2);
    
    arr2={10,20,30,40,50};
    
    display(arr1);
    display(arr2);
    
    std::cout<<"\nArray1 size: "<<arr1.size()<<'\n';
    std::cout<<"\nArray1 size: "<<arr2.size()<<'\n';
    
    arr1[0]=200;
    arr2.at(4)=300;
    
    display(arr1);
    
    std::cout<<"\nFront of arr2: "<<arr2.front()<<'\n';
    std::cout<<"\nBack of arr2: "<<arr2.back()<<'\n';
}

void test2() {
    std::cout<<"\n==========Test 2==============\n";
    std::array<int,5>arr1{1,2,3,4,5};    
    std::array<int,5>arr2{10,20,30,40,50};  

    display(arr1);
    display(arr2);    
    
    arr1.fill(0);
    display(arr1);
    display(arr2);
    
    arr1.swap(arr2);
    display(arr1);
    display(arr2); 
  
}

void test3() {
    std::cout<<"\n==========Test 3==============\n";
    std::array<int,5>arr1{1,2,3,4,5};   
    
    int* ptr=arr1.data();   // similar to *ptr=&arr1[0]
    std::cout<<ptr<<'\n';
    *ptr=1000;
    
    display(arr1);   
}

void test4() {
    std::cout<<"\n==========Test 4==============\n";
    std::array<int,5> arr1{2,1,4,5,3};
    display(arr1);
    
    std::sort(arr1.begin(), arr1.end());  // sort from smallest to largest
//    std::sort(arr1.begin(), arr1.end(), [](int x, int y){return y<x;});  // sorts from largest to smallest
    display(arr1);
}

void test5() {
    std::cout<<"\n==========Test 5==============\n";
    std::array<int,7> arr1{2,1,4,5,3,5,1};
   
    
    std::array<int,7>::iterator min_num=std::min_element(arr1.begin(), arr1.end());  // returns the first min 
    auto max_num=std::max_element(arr1.begin(), arr1.end());                         // return the first max
    std::cout<<"\n maximum: "<<*max_num<<" minimum: "<<*min_num<<'\n';
    
    auto mm=std::minmax_element(arr1.cbegin(), arr1.cend());    // returns a pair of iterators for first min and last max 
    std::cout<<*(mm.first)<<" "<<*(mm.second)<<'\n'
             <<std::distance(arr1.cbegin(), mm.second)+1<<'\n'  // returns the position of the max element
             <<std::distance(mm.first, mm.second)<<'\n'         // returns the distance btwn min and max
             <<std::distance(arr1.begin(), arr1.end())<<'\n';  
 
}

void test6() {
    std::cout<<"\n==========Test 6==============\n";
    std::array<int,5> arr1{2,1,3,3,5};
    display(arr1);
    
    auto adjacent=std::adjacent_find(arr1.begin(), arr1.end());
    if(adjacent!=arr1.end())
        std::cout<<"\nAdjacent element found with value: "<<*adjacent<<'\n';
    else
        std::cout<<"\nThere are no adjacenet elements..\n";
    
    auto custom_adjacent=std::adjacent_find(arr1.begin(), arr1.end(), 
                                        [](int elem, int next_elem){return next_elem==elem*2-1;});
    
    if(custom_adjacent!=arr1.end())
        std::cout<<"\nCustom Adjacent (y=2x-1) found with values (x,y): "<<*custom_adjacent<<" "<<*(custom_adjacent+1)<<'\n';
    else
        std::cout<<"\nNo custom adjacent (y=2x-1) found...\n";
}

void test7() {
    std::cout<<"\n==========Test 7==============\n";
    std::array<int,5> arr1{1,2,3,4,5};
    display(arr1);
    
    int total=std::accumulate(arr1.begin(), arr1.end(), 0);
    
    std::cout<<"\nSum of elements in arr1 is: "<<total<<'\n';
}

void test8() {
    std::cout<<"\n==========Test 8==============\n";
    std::array<int,10> arr1{1,2,3,1,2,3,3,3,1,1};
    
    int count=std::count(arr1.begin(), arr1.end(), 3);
    std::cout<<"\nNumber of 3 in the container is: "<<count<<'\n';
 
}

void test9() {
    std::cout<<"\n==========Test 9==============\n";
    std::array<int,10> arr1{1,2,3,50, 100, 200, 70, 80, 300, 60};
    
    int count=std::count_if(arr1.begin(), arr1.end(), 
                            [] (int x){return x>10 && x<200;});
    std::cout<<"\nNumber of values between 10 & 200 are: "<<count<<'\n';
    
    std::cout<<'\n';

}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    
 return 0;
}