#pragma once

#include <type_traits>
#include <functional>


template <typename TSignature>
class function_view;

template <typename TReturn, typename... TArgs>
class function_view<TReturn(TArgs...)> final
{
private:
    using signature_type = TReturn(void*, TArgs...);

    void* _ptr;
    TReturn (*_erased_fn)(void*, TArgs...);

public:
    template <typename T, typename = std::enable_if_t<
                              std::is_invocable<T, TArgs...>{} &&
                              !std::is_same<std::decay_t<T>, function_view>{}>>
    function_view(T&& x) noexcept : _ptr{(void*)std::addressof(x)}
    {
        _erased_fn = [](void* ptr, TArgs... xs) -> TReturn {
            return (*reinterpret_cast<std::add_pointer_t<T>>(ptr))(
                std::forward<TArgs>(xs)...);
        };
    }

    decltype(auto) operator()(TArgs... xs) const
        noexcept(noexcept(_erased_fn(_ptr, std::forward<TArgs>(xs)...)))
    {
        return _erased_fn(_ptr, std::forward<TArgs>(xs)...);
    }
};