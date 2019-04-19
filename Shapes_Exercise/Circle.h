#ifndef _CIRCLE_H
#define _CIRCLE_H
#include "Shapes.h"
#include <iostream>
#include "Vector3.h"

class Circle: public Shapes
{
public:
        Circle(const Vector3& c, float radius=0);
        void setCenter(const Vector3& c) {m_center=c;}
        Vector3 getCenter() const {return m_center;} 
        
        void setRadius(float r) {radius=r;}
        float getRadius() const {return radius;}
        
        virtual void draw() const override;
        
        virtual ~Circle()=default;

private:
  Vector3 m_center{};
  float radius{};
};

#endif // _CIRCLE_H