module;

#include <cstdint>
#include <concepts>

export module Kbza:Utils;

/// @brief 
/// @tparam T 
/// @param alignment 
/// @return 
template<std::unsigned_integral T>
constexpr T alignment_mask(T alignment)
{
    return ~alignment + 1;
}

export namespace Kbza
{

    /// @brief 
    /// @tparam T 
    /// @param value 
    /// @return 
    template<std::unsigned_integral T>
    constexpr bool is_power_of_two(T value)
    {
        return (~value + 1) + value == 0;
    }

    /// @brief 
    /// @tparam alignment 
    /// @tparam T 
    /// @param ptr 
    /// @return 
    template<int alignment, std::unsigned_integral T>
    constexpr bool is_aligned(T ptr)
    {
        return (ptr & ~alignment_mask(static_cast<std::uintptr_t>(alignment))) == 0;
    }

    /// @brief 
    /// @tparam alignment 
    /// @tparam T 
    /// @param ptr 
    /// @return 
    template<int alignment, std::unsigned_integral T>
    constexpr T align(T ptr)
    {
        return ptr & alignment_mask(static_cast<T>(alignment));
    }

}
