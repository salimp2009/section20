#ifndef _ILLEGAL_BALANCE_EXCEPTION_H
#define _ILLEGAL_BALANCE_EXCEPTION_H

#include <exception>


// Example for deriving an Exception class from C++ exception base class

class IllegalBalanceException : public std::exception
{
  public:
    IllegalBalanceException() noexcept=default;
    virtual ~IllegalBalanceException()=default;
    
    virtual const char* what() const noexcept {     // noexcept means it does not throw exception
        return "Illegal Balance...\n";
    }
};

class InsufficientFundsException : public std::exception
{
  public:
    InsufficientFundsException() noexcept=default;
    virtual ~InsufficientFundsException()=default;
    
    virtual const char* what() const noexcept {     // noexcept means it does not throw exception
        return "Insufficient Funds...\n";
    }
};

class NegativeAmountException : public std::exception
{
  public:
    NegativeAmountException () noexcept=default;
    virtual ~NegativeAmountException ()=default;
    
    virtual const char* what() const noexcept {     // noexcept means it does not throw exception
        return "Negative Amount Not Accepted...\n";
    }
};


#endif // _ILLEGAL_BALANCE_EXCEPTION_H