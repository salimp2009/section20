#ifndef TRUST_ACCOUNT_H
#define TRUST_ACCOUNT_H
#include "Savings_Account.h"
#include "Account.h"



class Trust_Account: public Savings_Account
{
private:
    static constexpr const char* def_name="Unnamed Trust Account";
    static constexpr double def_balance=0.0;
    static constexpr double def_int_rate=0.0;
    static constexpr double bonus=50.0;
    static constexpr double withdrawal_limit=0.2;
    static constexpr double amount_for_bonus=5000.0;
    static constexpr int max_withdrawal=3;
    
protected:
   int total_withdrawal{};
    
public:
    // one arg constructor
    Trust_Account(std::string name=def_name, double balance=def_balance, double int_rate=def_int_rate);
    
    
    // member functions
    virtual bool deposit(double amount) override;  //any deposit 5000 dollars or more will get 50 dollars bonus
    virtual bool withdraw(double amount) override; // 3 withdrawal per year; each withdrawal cannot exceed 20% of the balance
    
    virtual void print(std::ostream& os) const override;
    
    Trust_Account& operator+=(double amount);
    Trust_Account& operator-=(double amount);
    
    virtual ~Trust_Account()=default;
};

#endif //TRUST_ACCOUNT_H