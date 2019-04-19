#ifndef I_DRAW_H
#define I_DRAW_H
#include <iostream>

class I_Draw
{
    friend std::ostream& operator<<(std::ostream& os, const I_Draw& obj);
public:
    virtual void draw() const = 0;
    virtual ~I_Draw()=default;
};

#endif // I_DRAW_H