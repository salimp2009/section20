#ifndef _SHAPES_H
#define _SHAPES_H
#include <iostream>
#include "I_Draw.h"

class Shapes: public I_Draw
{
protected:
    
public:
    Shapes(int id=0);
    virtual void setID(const int id) { m_id=id;}
    int          getID() const {return m_id;}
    virtual void draw() const override = 0;  // no implemantation;
    virtual ~Shapes()=default;
private:
    int m_id{};
};

#endif //_SHAPES_H