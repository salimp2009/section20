#include <iostream>
#include <memory>

// Basic Example for an Pure Virtual class (Abstract Class)
// abstract, pure virtual class; does not need to have implemantation
// on pure virtual function but it can be
// destructor is needed and at least one pure virtual function


// Pure Virtual Abstract Interface Class that implements overloading operator
// that will work all the derived classes
// the drived classes will only override a member print() function
// this way we dont have define an overloaded friend insertion operator << for derived
// classes and will work better
class I_Printable 
{
    friend  std::ostream& operator<<(std::ostream& os, const I_Printable& obj); 
public:
    virtual void print(std::ostream& os) const=0;
    virtual ~I_Printable()=default;
};

std::ostream& operator<<(std::ostream& os, const I_Printable& obj) {
        obj.print(os);
        return os;
    }

class Shape: public I_Printable
{
public:
    virtual void draw()=0;       // pure virtual function
    virtual void rotate()=0;     // pure virtual function  
    virtual void print(std::ostream& os) const override {
        os<<"Shape is printing....\n";
    }
    virtual ~Shape() { };  
};

// if Derived class does not override it will be an abstract class
class Open_Shape: public Shape              // abstract class
{
public:
    virtual~Open_Shape()=default; 
};

class Closed_Shape: public Shape            // abstract class
{
public:
    virtual ~Closed_Shape()=default; 
};

class Line: public Open_Shape               // concrete class
{
public:
    virtual void draw() override {
        std::cout<<"Draw a line \n";       
    }
    virtual void rotate() override {
        std::cout<<"Rotate a line \n";       
    }
    virtual void print(std::ostream& os) const override {
        os<<"Line is printing....\n";
    }
    virtual ~Line(){std::cout<<"deleting Line..\n";}  
};

class Rectangle: public Closed_Shape        // concrete class
{
public:
    virtual void draw() override {
        std::cout<<"Draw a Rectangle \n";       
    }
    virtual void rotate() override {
        std::cout<<"Rotate a Rectangle \n";       
    } 
    
    virtual void print(std::ostream& os) const override {
        os<<"Rectangle is printing....\n";
    }
    
    virtual ~Rectangle() {std::cout<<"deleting Rectangle..\n";}  
};

using ShapePtr=std::shared_ptr<Shape>;
void draw_rotate( ShapePtr sp1, ShapePtr  sp2){
    std::cout<<"..........Function draw_rotate()..........\n";
    std::cout<<*sp1;
    sp1->draw();
    sp1->rotate();
    
    std::cout<<*sp2;
    sp2->draw();
    sp2->rotate();
}

int main()
{
    std::shared_ptr<Shape>shp1=std::make_shared<Line>();
    shp1->draw();
    shp1->rotate();
    //std::cout<<*shp1<<'\n';
    
    
    auto shp2=shp1;
    std::cout<<shp1.use_count()<<'\n';
    shp2->rotate();
    //std::cout<<*shp2<<'\n';
    
    // Closed_Shape x;          // compiler error; since it is an abstract class //
                                // a derived class from abstract; no override virtual function becomes abstract
                                    
    shp1.reset();
    shp1=std::make_shared<Rectangle>();
    shp1->draw();
    shp1->rotate();
    //std::cout<<*shp1<<'\n';
    
     draw_rotate(shp1, shp2);

    return 0;
}
