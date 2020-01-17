#include <iostream>
#include <ios>
#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>


int main()
{
  std::cout<<"Enter your favorite number between 1-100:";
  int favorite_number{0};
  //std::cin>>favorite_number;
  std::cout<<"you entered "<<favorite_number<<'\n';
  std::cout<<"That is my favorite number too :))\n";


    std::cout<<"enter an integer: ";
    int num1{0};
    std::cin>>num1;
    std::cout<<"The address of num1 is: "<<&num1
             <<"\nthe value is: "<<num1<<'\n';
    
    unsigned short int my_score{42};
//    std::cout<<std::hex<<my_score<<", plain my_score: "<<my_score<<'\n';
    std::cout<<my_score<<'\n';
    std::cout<<std::bitset<16>(my_score)<<'\n';
    
    long people_on_earth{7'600'000'000'000'000'000};
    std::cout<<people_on_earth<<'\n';
    std::cout<<std::bitset<64>(people_on_earth)<<'\n';
    
    
    short value1=30000;
    short value2=1000;
    auto product = value1*value2;                   // auto m{1} used to give initializer list type before c++17
   // auto m{1,2};                                  // auto m{1,2} is not allowed since c++17; before it was initiliazer_list<int>    
                                                    // auto is better used for expresssions auto m =....especially used for lambdas
    
    
    std::cout<<"product= "<<product<<'\n';
    std::cout<<"size of char: "<<sizeof(char)<<", max="<<+std::numeric_limits<char>::max()<<'\n';                   // + have to be added in front of std::numeric_limits<char>::max because
    std::cout<<"size of short: "<<sizeof(short)<<", max="<<std::numeric_limits<short>::max()<<'\n';                 // the return type is type T (template parameter) therefore it return char 
    std::cout<<"size of int: "<<sizeof(int)<<", max="<<std::numeric_limits<int>::max()<<'\n';                       // in order to conver the return type 
    std::cout<<"size of float: "<<sizeof(float)<<", max="<<std::numeric_limits<float>::max()<<'\n';                 // adding + sign turns it into arithmetic operation and to int    
    std::cout<<"size of double: "<<sizeof(double)<<", max="<<std::numeric_limits<double>::max()<<'\n';
    
    std::vector<float>vecn{1.,2.,4.,5.,7.,8.,9.,10.,12.};
    std::cout<<sizeof vecn<<'\n';
    std::cout<<vecn.max_size()<<'\n';
    
    int test_scores []{90,100,80,60};
    std::cout<<test_scores[0]<<'\n';
    std::cout<<*(test_scores+1)<<'\n';     // test_scores refers to first element +1 increments the address
                                           // * dereferences the address and we get the second element
    std::cout<<test_scores[0+1]<<'\n';           // array arithmetic is allowed
                                         
    char wovels[]{'s', 'a','l','i', 'm'};
    
    // algorithm can be used w/ row arrays 
    std::copy(std::begin(wovels), std::end(wovels),         // std::begin() will create an iterotor from the array
            std::ostream_iterator<char>(std::cout, " "));   // the value of each element is printed on the specified ostream
    std::cout<<'\n';                                        // it can be std:: cout or write a file as well
    
    std::cout<<sizeof wovels<<'\n';                         // sizeof give the number of elements of the array 

    
    std::cout<<*wovels<<'\n';              // the name of an array is the address of the first element [0]
                                           // if you dereference the name of array, you get the value of first element 
    
    
    std::iota(std::begin(wovels), std::end(wovels), 'c');  //std::iota increments the value of elements by one starting with the  
                                                           // given initial value e.g::'c'
    // printing the revised array
    std::copy(std::begin(wovels), std::end(wovels),         
            std::ostream_iterator<char>(std::cout, " "));
    std::cout<<'\n'; 
    
    // the name of array can be used to refer to address 
    std::copy(wovels, wovels +sizeof(wovels),              
            std::ostream_iterator<char>(std::cout, " "));
    std::cout<<'\n'; 
    
    // multi dimension array[row], [coloumn] 
    // row is the number of data set; each set has 4 elements
    int movie_ratings[3][4]{ 
            {0,4,5,6},{2,1,6,8}, {4,2,7,8}
            };
            
    // 1st data set 4th element
    std::cout<<movie_ratings[0][3]<<'\n';                                     // will give number 6
    std::cout<<&movie_ratings[0][0]<<" "<<&movie_ratings[0][1]                // memory addresses of elements of 1st data set; 
              <<" "<<&movie_ratings[0][2]<<" "<<&movie_ratings[0][3]<<'\n';   // it should be contigous; the address inreases by the size  
    
    // switch example
    int selection_case{5};                                                                           // the size of the type of the array; e.g. increment by 4   
    switch(selection_case)
    {
        case 2: 
            std::cout<<"case 2 \n";
            break;
        case 3: 
            std::cout<<"case 3 \n";
            break;
        case 5: std::cout<<"case 5 activated \n";
            break;
        default: 
            std::cout<<"getting out...\n";
    }
    
    // for loop example for multiple variable condition and iteration
    for(int i{1}, j{2}; i<5 && j<6; ++i, j+=2)
        std::cout<<i<<" + "<<j<<"= "<<i+j<<'\n';
        
    // print i in a table form; each line 10 numbers 
    for(int i{1}; i<100; ++i) {
        if(i%10==0) std::cout<<'\n';
        std::cout<<i<<" ";
    }
    
    std::cout<<'\n';
    
    // range based loop for c-style strings
    for(const auto& c: "that is funky") {
        std::cout<<(c==' ' ? '\t':c);          // alternative way for if condition
//        if(c==' ') std::cout<<'\t';         // putting a tab instead of a space; just for fun :)
//        std::cout<<c;
    }
    std::cout<<'\n';
    
    // typical while condition example
    std::cout<<"Enter a number to count down: ";
    int num{0};
    std::cin>>num;
    while(num>0) {
        std::cout<<"Count to lift off: "<<num<<'\n';
        --num;
    }
    std::cout<<"Lift Off !!!! : "<<num<<'\n';  

    // coun_if algorithm from STL
    std::vector<int>vec99(50,60);   // a vector of 50 elements; all are assigned value 60
    int num_to_count{60};
    auto total_count=std::count_if(vec99.begin(), vec99.end(), [num_to_count](const int num){ return num==num_to_count;});
    
    std::cout<<"total number of "<<num_to_count<<" in vector is: "<<total_count<<'\n';
    
    // do{  } while() loop example; checks the condition at the end !!
    // do loop continues until the while is false; if while cond is true it keeps running
    // for cases that needs at least one iteration do-while loop is preferred 
    // otherwise just while loop is OK
    char selection{};
    do {
        std::cout<<"please enter a width & a height: ";
        double width{0}, height{0};
        std::cin>>width>>height;
        
        std::cout<<"the area is: "<<width*height<<'\n';
        
        std::cout<<"\nDo you want to enter another width & height (Y or N) ? ";
        
        std::cin>>selection;
    } while (selection =='y' || selection=='Y');
    
    std::cout<<"Goodbye \n";
 
 
 return 0;
}