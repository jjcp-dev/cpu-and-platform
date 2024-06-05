module;

#include <concepts>
#include <type_traits>

export module Utils:Numbers;

export namespace Utils
{

    /// @brief
    /// @tparam T
    /// @param value
    /// @return
    template<std::integral T>
    constexpr bool is_power_of_two(T value)
    {
        std::make_unsigned_t<T> x = value;

        return x == 0 ? false 
                      : (x & (x - 1)) == 0;
    }

}
