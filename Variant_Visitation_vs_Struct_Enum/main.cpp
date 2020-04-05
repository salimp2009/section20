#include <iostream>
#include <variant>

enum class shape_type {circle, box};
constexpr static float  pi=3.14567;

struct  shape{
    shape_type _type;
    union 
    {
        struct { float _radius; }           circle_data;
        struct { float _width, _height; }   box_data; 
    } _udata; 
}; 

auto area (const shape& s) {
    switch(s._type) {
        case shape_type::circle:
        {
            const auto& r=s._udata.circle_data._radius;
            return pi*r*r;
        }
        
        case shape_type::box:
        {
            const auto& [w, h]=s._udata.box_data;
            return w*h;
        }
    };
}

struct circle { float _radius;};
struct box { float _width, _height;};
using vshape=std::variant<circle, box>;

auto area(const vshape& s) {
    struct {
        auto operator()(const circle& x) const { 
           return pi * x._radius *x._radius;
        }
        auto operator()(const box& x) const {
            return x._width * x._height;
        } 
    } visitor;
    
    return std::visit(visitor, s);
}

struct collision_resolver
{
    void operator()(circle, circle) { std::cout<<"Collision resolver: circle-circle...\n";}
    void operator()(circle, box) { std::cout<<"Collision resolver: circle-box...\n";}
    void operator()(box, box) {std::cout<<"Collision resolver: box-box...\n";}
    void operator()(box, circle) {std::cout<<"Collision resolver: box-circle...\n";}
};


// Example for Variadic Baes for multiple Bases in class, structs
// we can overload the operators to be able to use different types
struct foo_float { constexpr float operator()(float x) const {  return x; } };

struct foo_char { constexpr char operator()(char x) const { return x;} };

template<typename... Bases>
struct overloader:Bases...
{
    using Bases::operator()...;     //OK in C++17 but does not work C++14 or c++11
};

// alternative overloader with variadic bases & recursion
template<typename TF, typename... TFs>
struct overloader2: TF, overloader2<TFs...>
{
    using TF::operator();
    using overloader2<TFs...>::operator();
};

// specialization if there is one type TF other
template<typename TF>
struct overloader2<TF>:TF
{
    using TF::operator();
};

int main() 
{
    
    using foo=overloader<foo_float, foo_char>;
    auto xx=foo{}(23.5f);
    auto yy=foo{}('c');
    std::cout<<"float: "<<xx<<", char: "<<yy<<'\n';

    overloader2<foo_float, foo_char> overld2;
    static_assert(overld2(23.5f)==23.5f);
    static_assert(overld2('b')=='b');
    std::cout<<"overloader2 float: "<<overld2(55.666f)<<", overloader2 char: "<<overld2('h')<<'\n';
    

    shape s{shape_type::circle, {{2}} };
    shape s2{shape_type::box};
     
    s2._udata.box_data._width=2;
    s2._udata.box_data._height=5;   
    
    auto area1=area(s);
    std::cout<<"area of circle: "<<area1<<'\n';
    std::cout<<"check radius of s, circle radius: "<<s._udata.circle_data._radius<<'\n';
    
    auto area2=area(s2);
    std::cout<<"area of box: "<<area2<<'\n';
    
    vshape v0{circle{2}};
    vshape v1{box{3,5}};
    std::visit(collision_resolver{}, v0, v1);
   

    return 0;
}
