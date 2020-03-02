#ifndef MY_I_PRINT_H
#define MY_I_PRINT_H
#include <iostream>

class I_Print
{
    friend std::ostream& operator<<(std::ostream& os, const I_Print& obj);
public:
    virtual void print(std::ostream& os) const=0;
    virtual~I_Print()=default;
};

#endif // MY_I_PRINT_H
