#include <iostream>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <vector>
#include <tuple>

template<typename F, typename...Args>
void for_each_args(F&& fn, Args&&... args) {
    return (void) std::initializer_list<int> { 
        /* the () paranthesis evaluates the expersin inside it; which becomes
      // the element of the initializer list, (function(),0)
      // after the function the comma operator followed by zero evaluates it to an integer
      // so that initializer list accepts it 
      // after closing () paranthesis we continue to 
      // pass the args by the variadic ... expression
      */
        (fn(std::forward<Args>(args)),0)...};
};


template<typename...Args>
auto make_vector(Args&&...args) {
    
  using VectorType =std::common_type_t<Args...>; 
  
  std::vector<VectorType>result;
  result.reserve(sizeof ...(Args)); 
  
  for_each_args(
            [&result](auto&& x) {result.emplace_back(std::forward<decltype(x)>(x));}, 
            std::forward<Args>(args)...
  );
  return result;
    
};

template<typename F, typename Tuple, std::size_t ... I>
decltype(auto) sp_apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>) 
{
    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}


template<typename F, typename Tuple>
decltype(auto) sp_apply(F&& fn, Tuple&& t) 
{
    using Indices=std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>;
    return sp_apply_impl(std::forward<F>(fn), std::forward<Tuple>(t), Indices{});
}


 // Salim Implementation
template<typename FF, typename TTuple>
void forTuple(FF&& ffn,  TTuple&& tt) 
{
     sp_apply(
        [&ffn](auto&&... xs)
        { 
            for_each_args(ffn, std::forward<decltype(xs)>(xs)...); 
        }, 
        std::forward<TTuple>(tt)
     );
}

// example for std::index_sequence usage
// index_sequence returns integers of given amount during compile time 
// it is used for compile time computations mostly

// create a struct to print the created indexes; below is only forward declaration
template<typename>
struct seqPrint;

// create a specialized version of seqPrint 
// with a type matcing index_sequence
template<std::size_t... TInd>
struct seqPrint<std::index_sequence<TInd...>>
{
    // create a function that will print the passed Index number 
    // using forArgs
    static void print() {
    (std::cout<< ... <<TInd) <<'\n';
    ((std::cout<<TInd<<" "),...);
    std::cout<<'\n';
    std::cout<<"the size of integer sequence: "<<sizeof... (TInd)<<'\n';
    }
    
    // alternative way using for_each_args
    static void print_args() {
        
        // for_each_args will pass each index number TInd into lambda which will print the passed value
        for_each_args([](auto x){std::cout<<x<<" "; }, TInd...);
        std::cout<<'\n';
    }
    
};

using Seq0=std::make_index_sequence<10>;

/* Vitterio Romeo's Implemantation
//template <typename TF, typename... Ts>
//void forArgs(TF&& mFn, Ts&&... mArgs)
//{
//    return (void)std::initializer_list<int>{
//        (mFn(std::forward<Ts>(mArgs)), 0)...};
//}
//
//template <typename F, typename Tuple, size_t... I>
//decltype(auto) My_apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
//{
//    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
//}
//
//template <typename F, typename Tuple>
//decltype(auto) My_apply(F&& f, Tuple&& t)
//{
//    using Indices =
//        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>;
//
//    return My_apply_impl(std::forward<F>(f), std::forward<Tuple>(t), Indices{});
//}
//
//template <typename TFn, typename TTpl>
//void forTuple(TFn&& mFn, TTpl&& mTpl)
//{
//     We basically expand the tuple into a function call to
//     a variadic polymorphic lambda with `apply`, which in
//     turn passes the expanded tuple elements to `forArgs`,
//     one by one... which in turn calls `mFn` with every
//     single tuple element individually.
//
//    My_apply(
//         The callable object we will pass to `apply` is
//         a generic variadic lambda that forwards its
//         arguments to `forArgs`.
//        [&mFn](auto&&... xs)
//        {
//             The `xs...` parameter pack contains the
//             `mTpl` tuple elements, expanded thanks
//             to `apply`.
//
//             We will call the `mFn` unary function
//             for each expanded tuple element, thanks
//             to `forArgs`.
//            forArgs(mFn, std::forward<decltype(xs)>(xs)...);
//        },
//
//        std::forward<TTpl>(mTpl));
//}
*/


int main()
{
    // example for index_sequences which are helpfull
    // to avoid compile time recursion just like in the for tuple example
    // it is used to create an iteration instead of recursion which reduces compiles times
    seqPrint<Seq0>::print();
    seqPrint<Seq0>::print_args();
    
    seqPrint<std::make_index_sequence<20>>::print();
    
    
    // the input paramater of the lambda has to be const otherwise it gives 
    // an error ; this has to do with initializerlist uses a const iterator
     auto print=[](const auto& x){std::cout<<x<<'\n';};
    for_each_args(print, 45, 65, "salim");

    
    forTuple(
            [](const auto& x){std::cout<<x<<'\n';}, 
            std::make_tuple(100, "didem", 15.f)
            );
    
    auto vec=make_vector("didem", std::string("Sema"), "Demir");
    for(const auto& v:vec)
        std::cout<<v<<" ";
    
    std::cout<<'\n'<<std::boolalpha;
    std::cout<<std::is_same_v<decltype(vec), std::vector<std::string>><<'\n';
    
    static_assert(std::is_same<decltype(vec), std::vector<std::string>>(),"");
    
    
    
    return 0;
}
