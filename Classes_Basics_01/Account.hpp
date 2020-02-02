#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <iostream>
#include <string>

// std::move() makes copies more efficient instead of using const& for heavy types 
// such std::string or std::vector alternatively std::forward<>() can be used
// which will work for L-value & r-values

class Account
{
    static constexpr const char* default_name="default account";
    static constexpr double default_balance{0};
public:
    Account(std::string nm=default_name, double balance=default_balance) :
            name{std::move(nm)}, balance{std::move(balance)}          
            {std::cout<<"Account constructor called.."<<name<<'\n';}        // default values will be passed for a non-arg constructor 
                                                                            // if there is no default value or no specific no-args constructor 
                                                                            // we get a compiler error
    /* Typical copy constructor: NOT Recommend because this deletes default
    // compiler generated move constructor; if need to use then provide also
    // copy assignment, move constructor and move assignment and destructor
    //  Rule of Five 
    */
//    Account(const Account& source): name{source.name}, balance{source.balance}
                                  //{std::cout<<"Copy Constructor-Shallow Copy...\n";}

// destructor not needed unless there is a specific need;
//    ~Account() {std::cout<<"Account destructor called..."<<name<<'\n';}   
                                                                            // for specific members; eg raw pointers
/*  the automatic generation of move operations is disabled when one of the following special member functions is user-declared:
//    • copy constructor
//    • copy assignment operator
//    • destructor
//  even if use '=default;' definition for the above ones 
//  ~Account() = default;  // automatic move constructor disable; user has to provide 
 */
    
    void set_balance(double bal) {balance=std::move(bal);}
    double get_balance() const {return balance;}
    

    void set_name(std::string nm);
    std::string get_name() const;
    
    bool deposit(double amount);
    bool with_draw(double amount);
    
private:
    std::string name;
    double balance;
};

#endif // _ACCOUNT_H_