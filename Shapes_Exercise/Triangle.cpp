#include  "Triangle.h"

Triangle::Triangle(const Vector3 vertex[3]) 
            : m_vertex{vertex[0], vertex[1], vertex[2]}
            { }
            
Triangle::Triangle(const Vector3 v1, const Vector3 v2, const Vector3 v3)
                 : m_vertex{v1, v2, v3}
                //  : m_vertex{{v1.x, v1.y, v1.z},{v2.x, v2.y, v2.z},{v3.x, v3.y, v3.z}}
                 { }
 
  
void Triangle::setVertex(int i, const Vector3& v)
{
    m_vertex[i]=v;
}

    
void Triangle::draw() const 
{
    std::cout<<"\nDrawing Triangle: \n";
    for(const auto v:m_vertex)
        std::cout<<"["<<v.x<<", "<<v.y<<", "<<v.z<<"]\n";    
//    std::cout<<"First vertex (x,y,z): ["<<m_vertex[0].x<<", "<<m_vertex[0].y<<", "<<m_vertex[0].z<<"]\n";
//    std::cout<<"Second vertex (x,y,z): ["<<m_vertex[1].x<<", "<<m_vertex[1].y<<", "<<m_vertex[1].z<<"]\n";
//    std::cout<<"Second vertex (x,y,z): ["<<m_vertex[2].x<<", "<<m_vertex[2].y<<", "<<m_vertex[2].z<<"]\n";
}

void Triangle::setID(const int id)
{
    Shapes::setID(id);
    std::cout<<"\nTriangle ID is set to:"<<id<<'\n';    
}