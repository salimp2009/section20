#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "Shapes.h"
#include "Vector3.h"
#include <iostream>

class Triangle: public Shapes
{
public:
    Triangle(const Vector3 vertex[3]);
    Triangle(const Vector3 v1, const Vector3 v2, const Vector3 v3);
    void setVertex(int i, const Vector3& v);
    Vector3 getVertex(int i) const {return m_vertex[i];}
    
    virtual void draw() const override;
    virtual void setID(const int id) override;
    
    virtual ~Triangle()=default;
private:
    Vector3 m_vertex[3];
};


#endif // _TRIANGLE_H