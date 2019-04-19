#ifndef _I_PRINTABLE_H
#define _I_PRINTABLE_H
#include <iostream>

class I_Printable
{
    friend std::ostream& operator<<(std::ostream& os, const I_Printable& obj); 
public:
    virtual void print(std::ostream& os) const=0;
    virtual ~I_Printable()=default; 
};

#endif //_I_PRINTABLE_H