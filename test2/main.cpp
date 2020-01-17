#include <iostream>
#include <vector>
#include <functional>                   // used for std::accumulate
#include <numeric>                      // used for std::numeric_limits<>

char display_menu(char selection)
{
    std::cout<<"1. Do the move '1'\n";
    std::cout<<"2. Do the move '2'\n";
    std::cout<<"3. Do something else '2'\n";
    std::cout<<"Q. Quit\n";
    std::cin>>selection;
    return selection;
}

void selection_check(char selection)
{
    switch(selection) {
            case '1': 
                std::cout<<" Selected 1st move\n";
                break;
            case '2':
                std::cout<<" Selected 2nd move\n";
                break;
            case '3':
                std::cout<<" Selected 3rd move\n";
                break;
            default:
            {
                std::cout<<"invalid selection please try again !!!!\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                /* ignore is used for input stream to read from input stream the characters wanted
//                // from a given count number until a delimiter either a charcter or end of file
//                // in this case after we read the first we wanted all the remaining to be discarded
//                // therefore used std::numeric_limits<streamsize> to determine all the remaining and 
//                // \n indicated the end of line ; basically it mean discard all charcters on the line
//                // original form :
//                // basic_istream& ignore( std::streamsize count = 1, int_type delim = Traits::eof() );
//                */
            }
    }
}

// example for nested if loops; basics
void nested_loop()
{
    for(std::size_t num1{0}; num1<=10; ++num1) {
        for(std::size_t num2{0}; num2<=10; ++num2) {
            std::cout<<num1<<" * "<<num2<<"= "<<num1*num2<<'\n';
        }
        std::cout<<"-------------------------------\n";    
    }
}

void  accumulate_sum()
{
    std::vector<std::vector<int>>numbers {
        {1,2}, {1,3}, {3,2}, {4,2} };
    
    auto sum=std::accumulate(numbers.begin(), numbers.end(), 0,                                  // specifiy the start and end of container and initial value
                            [](int val, std::vector<int>n){return std::move(val)+n[0]*n[1]; });  // accumulate takes the initial value and first element of the container  
    std::cout<<sum<<'\n';                                                                       // and sums the initial value and returns a new initial  value for the next operation
}                                                                                               // when we specifiy the our own function the first element in lambda is the initial value,
                                                                                                // the second is the first element of vector; in this case it is a vector two with two element
                                                                                                // and we mulpily those two elements and add it to initial value
                                                                                                // std::move(val) is used so we dont have to create a copy; 
                                                                                                // std::move(init) will be default in C++20
                                                                                                
int main()
{
//    char selection{};
//    do{
//        
//        selection=display_menu(selection);
//        selection_check(selection);
//        
//    } while(selection!='q'&& selection!='Q');
//    
//    std::cout<<"Goodbye.....\n";
//    
//    nested_loop();
    
    accumulate_sum();
    
    return 0;
}
