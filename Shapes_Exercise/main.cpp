#include <iostream>
#include "Shapes.h"
#include "Circle.h"
#include "Triangle.h"
#include <vector>
#include "Shapes_Utility.h"
#include <memory>



int main()
{
    
    Shapes* p1=new Circle(Vector3{2.2f, 1.3f, 1.5f}, 5.0f);
    std::cout<<*p1<<'\n';
    p1->draw();

    Shapes* p2=new Circle(0, 3);
    
    std::cout<<"Circle p2 ID: "<<p2->getID();
    
    Vector3 vertex[]={{1.1f,2.1f, 3.2f}, {0.2f, 0.5f, 1.1f}, {2.1f, 3.2f, 4.5f}}; 
    Shapes* p3=new Triangle{vertex};
    p3->draw();
    p3->setID(3);
    
    std::shared_ptr<Shapes>p4{new Triangle{vertex}};  // there is a better way by using
    p4->setID(5);                                     // std::make_shared...
   
    std::unique_ptr<Shapes>p5=std::make_unique<Circle>(Vector3{1.2f, 1.3f, 0.5f}, 6.2f);
    p5->draw();
    
    auto p6=std::make_shared<Triangle>(Vector3{1.1f,2.1f, 3.2f}, Vector3{0.2f, 0.5f, 1.1f}, Vector3{2.1f, 3.2f, 4.5f});
    p6->draw();
    
    std::vector<Shapes*> shapes={p1, p2, p3};
    for(const auto shape:shapes)
        shape->draw();
    
    draw(shapes);
        
    std::cout<<'\n';
    
    delete p1;
    delete p2;
    delete p3;
    
 return 0;
}