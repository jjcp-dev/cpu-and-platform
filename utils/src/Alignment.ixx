module;

#include <cstdint>
#include <concepts>
#include <type_traits>

export module Utils:Alignment;

import :Numbers;

/// @brief 
/// @tparam T 
/// @param alignment 
/// @return 
template<std::integral T>
constexpr T alignment_mask(T alignment)
{
    return ~alignment + 1;
}

export namespace Utils
{

    /// @brief
    /// @tparam alignment
    /// @tparam T
    /// @param ptr
    /// @return
    template<int alignment, std::integral T>
    constexpr bool is_aligned(T ptr)
    {
        static_assert(Utils::is_power_of_two(alignment));

        return (ptr & ~alignment_mask(alignment)) == 0;
    }

    /// @brief 
    /// @tparam alignment 
    /// @tparam T 
    /// @param ptr 
    /// @return 
    template<int alignment, std::integral T>
    constexpr T align(T ptr)
    {
        static_assert(Utils::is_power_of_two(alignment));

        return ptr & alignment_mask(static_cast<T>(alignment));
    }

}
