#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <iostream>

class Vector3
{
public:
    Vector3(float x=0.0f, float y=0.0f, float z=0.0f);
    void set_xyz(float x, float y, float z);
    
    ~Vector3(){}
    
    float x{};
    float y{};
    float z{}; 
};

#endif //_VECTOR_H