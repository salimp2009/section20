#include <iostream>
#include <variant>
#include <tuple>
#include <memory>
#include "Match_Variant.hpp"

using number = int;

struct plus {};

struct minus {};

using op=std::variant<plus, minus>;

struct expr;

using r_expr=std::tuple<number, op, expr>;

struct expr 
{  
   // member data;
  std::variant<number, std::unique_ptr<r_expr> > _data;  // works OK because std::unique_ptr may be constructed for an incomplete type T, 
                                                       //such as to facilitate the use as a handle in the pImpl (Pointer to Implementation) idiom. See https://en.cppreference.com/w/cpp/language/pimpl 
                                                       // If the default deleter is used, T must be complete at the point in code where the deleter is invoked,   
  
  // std::variant<number, r_expr> _data;                // compile error; expr is not complete because it refers r_epxr
                                                        // and r_expr refers to expr ; it creates endless recursion
  
  // constructor for variadic arguments
  template<typename... Ts>
  expr(Ts&&... xs): _data{std::forward<Ts>(xs)...} { }                                      

};


template<typename TVisitor, typename... TVariants>
constexpr decltype(auto) visit_recursively(TVisitor&& visitor, TVariants... variants)
{
    return std::visit(std::forward<TVisitor>(visitor), std::forward<TVariants>(variants)._data ...);
}

// Getting compiler error; Not found the error ; code matches with the example
// but compiler complaints that visitor has to exhaust all the option in variantss ????
// problem seems to be in match function although it is supposed to get multiple variants
// it gives an error to somehow all the variants needs to be forwarded

//struct evaluator
//{
//    auto operator() (number x) { return x;}
//    auto operator() (const std::unique_ptr<r_expr>& x)
//    {
//        const auto& [lhs, op, rhs]=*x;
//        //const auto rest=std::visit(*this, rhs._data);
//        const auto rest=std::visit_recursively(*this, rhs);
//        
//        return match(op)( [&](plus) { return lhs+rest;},
//                          [&](minus){ return lhs-rest;} );
//    }
//};

int main()
{
    expr e0{5};
    
    expr e1{std::make_unique<r_expr>(9,plus{}, 3)};
    
    expr e2{std::make_unique<r_expr>(1, minus{}, std::make_unique<r_expr>(3, plus{}, 7))};
    
    //std::cout<<std::visit(evaluator{}, e1._data)<<'\n';
    
    const std::unique_ptr<r_expr> x=std::make_unique<r_expr>(3, plus{}, 7);
    
    const auto& [lhs, op, rhs]=*x;
    
    std::cout<<lhs<<'\n';
    
    return 0;
}
