module;

#include <cstdint>
#include <optional>

export module Kbza:Address;

import :Utils;

export namespace Kbza
{

    /// @brief
    /// @tparam alignment
    template <int alignment>
    class Address
    {
        static_assert(alignment > 0);
        static_assert(Kbza::is_power_of_two((unsigned) alignment));

    public:
        constexpr Address() = default;

        /// @brief
        /// @tparam other_alignment
        /// @param other
        template <int other_alignment>
        explicit constexpr Address(const Address<other_alignment>& other)
        {
            static_assert(other_alignment >= alignment);
            static_assert(Kbza::is_power_of_two((unsigned) other_alignment));

            address = other.value();
        }

        /// @brief
        /// @tparam other_alignment
        /// @param rhs
        /// @return
        template <int other_alignment>
        constexpr Address<alignment>& operator=(const Address<other_alignment>& rhs)
        {
            static_assert(other_alignment > alignment);
            static_assert(Kbza::is_power_of_two((unsigned) other_alignment));

            address = rhs.value();

            return *this;
        }

        /// @brief
        /// @param rhs
        /// @return
        constexpr auto operator+(int rhs) const -> Address<alignment>
        {
            return Address<alignment>(address + rhs * alignment);
        }

        /// @brief
        /// @param rhs
        /// @return
        constexpr auto operator-(int rhs) const -> Address<alignment>
        {
            return Address<alignment>(address - rhs * alignment);
        }

        /// @brief
        /// @param rhs
        /// @return
        constexpr auto operator+=(int rhs) -> Address<alignment>&
        {
            address += (std::int64_t)rhs * alignment;
            return *this;
        }

        /// @brief
        /// @param rhs
        /// @return
        constexpr auto operator-=(int rhs) -> Address<alignment>&
        {
            address -= (std::int64_t)rhs * alignment;
            return *this;
        }

        /// @brief
        /// @param value
        /// @return
        static constexpr auto create(std::uint64_t value) -> std::optional<Address<alignment>>
        {
            if (Kbza::is_aligned<alignment>(value))
            {
                return Address{ value };
            }
            else
            {
                return {};
            }
        }

        /// @brief
        /// @param value
        /// @return
        static constexpr auto create_aligned(std::uint64_t value) -> Address<alignment>
        {
            return Address<alignment>(Kbza::align<alignment>(value));
        }

        /// @brief
        /// @return
        constexpr auto value() const
        {
            return address;
        }

    private:
        std::uint64_t address = 0;

        explicit Address(std::uint64_t ptr)
            : address{ ptr } {}
    };

}
