#include <iostream>
#include "function_view.hpp"

// example for a lightweight function wrapper with a better performance 
// from std::function creates a very big code and cannot be optimized

template<typename TSignature>
class function_ref;

template<typename TReturn, typename...TArgs>
class function_ref<TReturn(TArgs...)> final
{
private:
    using signature_type=TReturn(void*, TArgs...);
    
    void* _ptr;
    TReturn(*_erased_fn)(void*, TArgs...);
public:

    template<typename T, typename=std::enable_if<std::is_invocable_v<T, TArgs...> 
                                        && !std::is_same_v<std::decay_t<T>, function_ref>>>
    function_ref(T&& x) noexcept :_ptr{(void*)&x}
    {
        _erased_fn=[](void* ptr, TArgs... xs) ->TReturn
        {
            return (*reinterpret_cast<std::add_pointer_t<T>>(ptr)) (std::forward<TArgs>(xs)...);
                   // *reinterpret_cast<std::add_pointer_t<T>>(ptr)
        };
    }
    
    decltype(auto) operator()(TArgs... xs) const
    {
        return _erased_fn(_ptr, std::forward<TArgs>(xs) ...);
    }
};

int foo_v(function_ref<int(int)> f, int a=0)
{
    return f(a);
}

int foo(function_view<int()> f)
{
    return f();
}

int main()
{
    auto l=[i=0]()mutable{return i+=5;};
    auto l2=[i=0](int y)mutable->int{return i+=y*5;};
    std::cout<<foo(l)<<'\n';
    std::cout<<foo_v(l2, 5)<<'\n';
 
    
    auto lessThan=[](auto y) {
        return [y](auto n) { return n<y;};
    };

    auto lessThan_Five=lessThan(5);
    
    std::cout<<lessThan_Five(3)<<'\n';
    std::cout<<lessThan_Five(10)<<'\n';
    
    
    return 0;
}
