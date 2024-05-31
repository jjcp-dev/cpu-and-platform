module;

#include <cstdint>
#include <optional>

export module Kbza:Address;

import :Utils;

export namespace Kbza
{

    /// @brief Aligned 64bit address wrapper
    ///
    /// Use this class to request for addresses that are guaranteed to
    /// be aligned as expected.
    ///
    /// @tparam alignment The alignment in bytes of the address
    template <int alignment>
    class Address
    {
        static_assert(alignment > 0, "Alignment must be greater than 0");
        static_assert(Kbza::is_power_of_two((unsigned)alignment), "Alignment must be a power of two");

    public:
        /// @brief Construct an address with a value of 0
        ///
        /// NOTE: 0 is always properly aligned
        ///
        constexpr Address() = default;

        /// @brief Copy constructor
        ///
        /// You can construct a copy from another address as long as the other
        /// address' alignment is greater or equal to the current one.
        ///
        /// @tparam other_alignment The alignment of the `other` address
        /// @param other The address to copy from
        template <int other_alignment>
        explicit constexpr Address(const Address<other_alignment>& other)
        {
            static_assert(other_alignment >= alignment, "Expected greater or equal alignment for copy-ctor");

            address = other.value();
        }

        /// @brief Copy constructor
        ///
        /// You can copy from another address as long as the other
        /// address' alignment is greater or equal to the current one.
        ///
        /// @tparam other_alignment The alignment of the `other` address
        /// @param rhs The address to copy from
        /// @return A reference to the current instance
        template <int other_alignment>
        constexpr Address<alignment>& operator=(const Address<other_alignment>& rhs)
        {
            static_assert(other_alignment >= alignment, "Expected greater or equal alignment for copy-assignment");

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

        /// @brief Try to create an Address with the given value
        /// @param value The address to construct
        /// @return An empty optional if `value` is not aligned to `alignment`
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

        /// @brief Create an Address with the closest aligned address to value (<= value)
        /// @param value The address to construct
        /// @return A properly aligned Address
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
