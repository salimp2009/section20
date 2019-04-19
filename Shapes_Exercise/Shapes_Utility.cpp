#include "Shapes_Utility.h"


void draw(const std::vector<Shapes*>& shapes)
{
    std::cout<<"============Drawing Shapes================\n";
    for(const auto shape:shapes)
        shape->draw(); 
    std::cout<<'\n';
}