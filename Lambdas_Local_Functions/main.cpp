#include <iostream>

// Example for using Lamdas as Local Functions to provide better interface

class Render_engine {
public:
    bool init_step0() { return true;}
    bool init_step1() { return false;}
    bool init_step2() { return true;}
    
    // classic way of several initiliaze with if statements
    bool initialize()
    { 
        if (!init_step0()) {
            std::cout<<"\nstep0 is failed."<<'\n';
            return false;
        }
        if(!init_step1()) {
            std::cout<<"\nstep1 is failed.."<<'\n';
            return false;
        }
        if(!init_step2()) {
            std::cout<<"\nstep2 is initialized.."<<'\n';
            return false;
        }
        return true;
    }
    
    // alternative initialize with a local function lambda 
    // which captures the local or member functions that initialize each step 
    bool initialize_with_lambda() {
        // define a local function to accept member function as a argument and 
        // run the called local / member function in the body of the lambda
        // so we can pass different functions as an argument and combine to
        // check differenet scenarios or create interfaces
        const auto try_step=[](auto f, const char* name) 
        { if(f()) return true;
          std::cerr<<name<<" failed..\n";
          return false;
        };
        
        // calling local function with the member functions as arguments
        return try_step([&]{return init_step0();}, "step0") && 
               try_step([&]{return init_step1();}, "step1") &&
               try_step([&]{return init_step2();}, "step2");
    }
    
    // classic way to print the status of by checking 
    //the status of various members / variable 
    void print_status() 
    {
        std::cout<<"progress function called" <<'\n';
        if(name!=nullptr) {std::cout<<*name<<'\n';}
        if(ptr!=nullptr) {std::cout<<*ptr<<'\n';}
        if(url!=nullptr) {std::cout<<*url<<'\n';}
        std::cout<<"\naction function called..\n";
    }
    
    // alternative way using lambda as local function 
    // creating a local lambda function that checks a variable and print status
    // second lambda action performs an operation
    // idea is to find way to sort the actions and create a lmbda for each action ttype
    // so we can pass several variable to same lambda function
    void print_status_lambda() 
    {
        auto action=[](const char* name) {std::cout<<name<<" function called with lambda..\n";};
        auto status=[](auto field){ if(field!=nullptr) std::cout<<*field<<'\n';};
        
        action("progress status");
        status(name);
        status(ptr);
        status(url);
        action("action time");
    }
    
    
  private:
    const char* name{"salim"};
    int* ptr{nullptr};
    const char* url{"www.gomovies.co"};
};

int main()
{
    Render_engine render;
    
    render.initialize();
    render.print_status();
    render.print_status_lambda();

 
 return 0;
}