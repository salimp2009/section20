#include <iostream>
#include <optional>
#include <string_view>

// tried to implement std::optional<> and std::string_view<>
// in exception; not the best use it is better not use the exception
// and make use of std::nullopt that std::optional returns when there is an error
// and check it in the main before using the returned value
// string_view is a better option than std::string since
// it does not make a copy it is basically a pointer the string object
// that was created 
// although compilers use SSO ; short string optimization; 
// for it is 16 characters, Clang used 20 characters


// custom classes can be used for exception handling; it can have members and methods
class DividebyZeroException { };

class NegativeValueException { };

std::optional<double> calculate_mpg(int miles, int gallons) {
    if(gallons==0 || miles ==0) 
       // throw std::nullopt;
        throw DividebyZeroException{ };                    // alternative; throw an object;
    if(gallons<0 || miles <0)
        // throw std::string_view{"Negative value error"};  // returnning a string_view is considered very very dangerous
        // throw std::runtime_error{"Negative value error"};  // as the lifetime of a string_view can depends on the object it refers to; 
        throw NegativeValueException{ };
    return static_cast<double>(miles)/gallons;             // in this case it is a temp object which will be destroyed           
}                                                          // the best use is when a string to a function and do some operations within the function
                                                           // string_view is a raw pointer to a char !!!! USE WITH CAUTION 
int main()
{
    std::cout<<"\n enter the miles: ";
    int miles{0};
    std::cin>>miles;
    std::cout<<"\n enter the gallons: ";
    int gallons{0};
    std::cin>>gallons;
    
    try {
    auto miles_per_gallon = calculate_mpg(miles, gallons);
    std::cout<<"\n Result: "<<miles_per_gallon.value()<<'\n';
    
//    } catch(std::string_view ex) {                            // using string_view might be unsafe here because the 
                                                                // lifetime of the string_view depends on the object it refers   
//        std::cerr<<"Negative Value Not Accepted....\n";       // in this example it refers to a temp object returned and it might 

    } catch(std::nullopt_t ex) {
        std::cerr<<"Divide by Zero Not Accepted..\n";

    } catch(DividebyZeroException& ex) {
        std::cerr<<"Divide by Zero Not Accepted..\n";
   
    } catch(NegativeValueException& ex) {
        std::cerr<<"Negative Value Not Accepted....\n";
    
    } catch(std::runtime_error& ex) {
        std::cerr<<ex.what()<<'\n';
   }  catch(...) {
        std::cerr<<"Unknow error....\n";
    }

    std::cout<<"GoodBye...\n";

    return 0;
}
