#ifndef _FUNCTION_REF_H
#define _FUNCTION_REF_H

#include <functional>
#include <type_traits>


template<typename Signature>
class function_ref;

template<typename Return, typename... Args>
class function_ref<Return(Args...)> final
{
private:
    using signature_type = Return(void*, Args...);
    void* _ptr;                                     // will refer to the address of the object ; which will be type-erased
    Return(*_erased_fn)(void*, Args...);            // this will be the address of of the erased operator() and store it as a function pointer
    
public:
    
    template <typename T, typename = std::enable_if_t<
                              std::is_invocable<T&, Args...>{} &&
                              !std::is_same<std::decay_t<T>, function_ref>{}>>
    function_ref(T&& x) noexcept : _ptr{(void*)std::addressof(x)}                                 // &x is the address of the callable of the object 
    {
        _erased_fn=[](void* ptr, Args...xs)->Return {
            return (*reinterpret_cast<std::add_pointer_t<T>>(ptr))(
            std::forward<Args>(xs)...); 
         };
    }
    
    decltype(auto) operator()(Args...xs) const noexcept(noexcept(_erased_fn(_ptr, std::forward<Args>(xs)...)))
    {                                                           // this is function_ref operator()
        return _erased_fn(_ptr, std::forward<Args>(xs)...);     // it will invoke type erased function _erased_fn
                                                                // pointer _ptr and all the arguments
                                                                // decltype(auto) is used to preserve the references 
    }
};


#endif // _FUNCTION_REF_H