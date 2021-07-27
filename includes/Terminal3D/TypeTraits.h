#pragma once

#include <stddef.h>

template<size_t T, size_t U>
struct is_same_integral
{
    static constexpr bool value = false;
};

template<size_t T>
struct is_same_integral<T, T>
{
    static constexpr bool value = true;
};

template<size_t T, size_t U>
constexpr bool is_same_integral_v = is_same_integral<T, U>::value;