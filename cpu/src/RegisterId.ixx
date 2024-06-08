module;

#include <cstdint>

export module Cpu:RegisterId;

export namespace Cpu
{

    /// @brief
    class RegisterId
    {
    public:
        struct ProgramCounterId { };
        struct StatusId { };

        static constexpr auto ProgramCounter = ProgramCounterId();
        static constexpr auto Status = StatusId();

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

        static constexpr RegisterId stack()
        {
            return RegisterId(15);
        }

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
