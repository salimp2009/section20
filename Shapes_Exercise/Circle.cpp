#include "Circle.h"

Circle::Circle(const Vector3& c, float radius)
            :m_center{c}, radius{radius} { }


void Circle::draw() const
{
    std::cout<<"\nDrawing circle center: "<<m_center.x<<", "<<m_center.y<<", "<<m_center.z
            <<", Radius: "<<radius<<'\n';
}            
            