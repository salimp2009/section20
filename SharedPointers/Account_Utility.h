#ifndef _ACCOUNT_UTILITY_H
#define _ACCOUNT_UTILITY_H
#include <vector>
#include "Account.h"


// Utility functions for Account class; will apply to all inherited classes
void display(const std::vector<Account*> &accounts);
void deposit(std::vector<Account*> &accounts, double amount);
void withdraw(std::vector<Account*> &accounts, double amount);


#endif //_ACCOUNT_UTILITY_H