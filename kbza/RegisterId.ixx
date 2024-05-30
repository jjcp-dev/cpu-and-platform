module;

#include <cstdint>

export module Kbza:RegisterId;

export namespace Kbza
{

    /// @brief
    class RegisterId
    {
    public:
        /// @brief
        /// @param id
        explicit constexpr RegisterId(std::uint8_t id)
        {
            value = id & 0x0F;
        }

        constexpr RegisterId(const RegisterId&) = default;
        constexpr RegisterId(RegisterId&&) = default;

        constexpr RegisterId& operator=(const RegisterId&) = default;
        constexpr RegisterId& operator=(RegisterId&&) = default;

        constexpr bool operator==(const RegisterId&) const = default;
        constexpr bool operator!=(const RegisterId&) const = default;

        /// @brief
        /// @return
        constexpr auto number() const
        {
            return value;
        }

    private:
        std::uint8_t value;
    };

}
