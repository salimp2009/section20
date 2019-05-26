#ifndef _FUNCTION_REF_ORG_H
#define _FUNCTION_REF_ORG_H

#include <functional>
#include <type_traits>

template <typename Signature>
class function_ref;

template <typename Return, typename... Args>
class function_ref<Return(Args...)> final
{
private:
    using signature_type = Return(void*, Args...);

    void* _ptr;
    Return (*_erased_fn)(void*, Args...);

public:
    template <typename T, typename = std::enable_if_t<
                              std::is_invocable<T&, Args...>{} &&
                              !std::is_same<std::decay_t<T>, function_ref>{}>>
    function_ref(T&& x) noexcept : _ptr{(void*)std::addressof(x)}
    {
        _erased_fn = [](void* ptr, Args... xs) -> Return {
            return (*reinterpret_cast<std::add_pointer_t<T>>(ptr))(
                std::forward<Args>(xs)...);
        };
    }

    decltype(auto) operator()(Args... xs) const
        noexcept(noexcept(_erased_fn(_ptr, std::forward<Args>(xs)...)))
    {
        return _erased_fn(_ptr, std::forward<Args>(xs)...);
    }
};

#endif // _FUNCTION_REF_ORG_H