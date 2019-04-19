#include "I_Draw.h"

std::ostream& operator<<(std::ostream& os, const I_Draw& obj)
{
    obj.draw();
    return os;
}
