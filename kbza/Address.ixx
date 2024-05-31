module;

#include <cstdint>
#include <optional>

export module Kbza:Address;

import :Utils;

export namespace Kbza
{

    /// A 64bit memory address that is guaranteed to be properly aligned.
    ///
    /// @tparam alignment The address' alignment in bytes (e.g: 1, 2, 4, ...)
    template <int alignment>
    class Address
    {
        static_assert(alignment > 0, "Alignment must be greater than 0");
        static_assert(Kbza::is_power_of_two((unsigned)alignment), 
                      "Alignment must be a power of two");

    public:
        /// Construct a null address (value = 0).
        ///
        /// An address of 0 is always aligned to any valid `alignment`
        constexpr Address() = default;

        /// Copy constructor.
        ///
        /// You can construct a copy from another address as long as the other
        /// address' alignment is greater or equal to the current one.
        ///
        /// Example:
        ///     auto a = Address<4>::create_aligned(1024);
        ///     auto b = Address<2>(a); // Since a is over-aligned in comparison
        ///                             // to b, this copy is guaranteed to be 
        ///                             // valid.
        ///
        /// @tparam other_alignment The alignment of the `other` address
        /// @param other The address to copy from
        template <int other_alignment>
        explicit constexpr Address(const Address<other_alignment>& other)
        {
            static_assert(other_alignment >= alignment, 
                          "Expected greater or equal alignment for copy-ctor");

            address = other.value();
        }

        /// Copy assignment.
        ///
        /// You can copy from another address as long as the other
        /// address' alignment is greater or equal to the current one.
        ///
        /// Example:
        ///     auto a = Address<4>::create_aligned(1024);
        ///     auto b = Address<2>::create_aligned(8);
        ///     
        ///     b = a; // Since a is over-aligned in comparison
        ///            // to b, this copy is guaranteed to be 
        ///            // valid.
        ///
        /// @tparam other_alignment The alignment of the `other` address
        /// 
        /// @param rhs The address to copy from
        /// 
        /// @return A reference to the current instance
        template <int other_alignment>
        constexpr Address<alignment>& operator=(const Address<other_alignment>& rhs)
        {
            static_assert(other_alignment >= alignment, 
                          "Expected greater or equal alignment for copy-assignment");

            address = rhs.value();

            return *this;
        }

        /// Computes current Address plus `rhs` elements 
        /// (rhs * alignment).
        ///
        /// Example:
        ///   auto x = Kbza::Address<2>::create_aligned(4);
        ///   (x + 1).value() == 6
        ///   (x + (-1)).value() == 2
        ///
        /// @param rhs The number of elements to move the address by
        /// 
        /// @return A new updated Address aligned to `alignment`
        constexpr auto operator+(int rhs) const -> Address<alignment>
        {
            return Address<alignment>(address + rhs * alignment);
        }

        /// Computes current Address minus `rhs` elements 
        /// (rhs * alignment).
        ///
        /// Example:
        ///   auto x = Kbza::Address<2>::create_aligned(4);
        ///   (x - (-1)).value() == 6
        ///   (x - 1).value() == 2
        ///
        /// @param rhs The number of elements to move the address by
        /// 
        /// @return A new updated Address aligned to `alignment`
        constexpr auto operator-(int rhs) const -> Address<alignment>
        {
            return Address<alignment>(address - rhs * alignment);
        }

        /// Add-assignment operator.
        /// 
        /// @param rhs The number of elements to move address by
        /// 
        /// @return Reference to this address
        constexpr auto operator+=(int rhs) -> Address<alignment>&
        {
            address += (std::int64_t)rhs * alignment;
            return *this;
        }

        /// Sub-assignment operator.
        /// 
        /// @param rhs The number of elements to move address by
        /// 
        /// @return Reference to this address
        constexpr auto operator-=(int rhs) -> Address<alignment>&
        {
            address -= (std::int64_t)rhs * alignment;
            return *this;
        }

        /// Try to create an Address with the given value.
        /// 
        /// @param value The address to construct
        /// 
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

        /// Create an Address with the closest aligned address to value (<= value).
        /// 
        /// Example:
        ///     auto x = Address<2>::create_aligned(3);
        ///     x.value() == 2;
        /// 
        /// @param value The address to construct
        /// 
        /// @return A properly aligned Address
        static constexpr auto create_aligned(std::uint64_t value) -> Address<alignment>
        {
            return Address<alignment>(Kbza::align<alignment>(value));
        }

        /// Get internal address value.
        /// 
        /// @return a 64bit address
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
