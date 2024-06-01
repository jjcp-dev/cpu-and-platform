module;

#include <cstdint>

export module Kbza:Instruction;

import :Opcode;
import :RegisterId;

export namespace Kbza
{

    /// Helper for decoding/encoding an instruction
    class Instruction
    {
    public:

        /// @brief 
        /// @param encoded 
        explicit constexpr Instruction(std::uint16_t encoded)
            : instruction{ encoded }
        { }

        /// @brief 
        constexpr Instruction()
            : Instruction{ 0 } // mov r0, 0x00
        { }

        constexpr Instruction(const Instruction&) = default;
        constexpr Instruction(Instruction&&) = default;

        constexpr Instruction& operator=(const Instruction&) = default;
        constexpr Instruction& operator=(Instruction&&) = default;

        constexpr bool operator==(const Instruction&) const = default;
        constexpr bool operator!=(const Instruction&) const = default;

        /// @brief 
        /// @return 
        constexpr Opcode opcode() const
        {
            auto opcode = instruction & 0x8000
                        ? instruction & 0xFF00 
                        : instruction & 0xF000;

            switch (opcode)
            {
            // Instruction block with a single register as parameter
            case 0xA000: 
            case 0xA100:
                return static_cast<Opcode>(instruction & 0xFFF0);
            // Instruction block with no parameters
            case 0xFF00:
                return static_cast<Opcode>(instruction);
            default:
                return static_cast<Opcode>(opcode);
            }
        }

        /// @brief 
        /// @return 
        constexpr std::uint16_t reg1() const
        {
            return instruction & 0x000F;
        }

        /// @brief 
        /// @return 
        constexpr std::uint16_t reg2() const
        {
            return (instruction & 0x00F0) >> 4;
        }

        /// @brief 
        /// @return 
        constexpr std::uint8_t imm4() const
        {
            return (instruction & 0x00F0) >> 4;
        }

        /// @brief 
        /// @return 
        constexpr std::uint8_t imm8() const
        {
            return (instruction & 0x0FF0) >> 4;
        }

        /// @brief 
        /// @return 
        constexpr std::uint16_t imm12() const
        {
            return instruction & 0x0FFF;
        }

        /// @brief 
        /// @return 
        constexpr std::int8_t signed_imm4() const
        {
            const auto imm = imm4();
            std::int8_t extended = (imm & 0x08)
                                  ? 0xF0 | imm
                                  : imm;

            return extended;
        }

        /// @brief 
        /// @return 
        constexpr std::int8_t signed_imm8() const
        {
            return static_cast<std::int8_t>(imm8());
        }

        /// @brief 
        /// @return 
        constexpr std::int16_t signed_imm12() const
        {
            const auto imm = imm12();
            std::int16_t extended = (imm & 0x0800)
                                  ? 0xF000 | imm
                                  : imm;

            return extended;
        }

        /// @brief 
        /// @return 
        constexpr std::uint16_t encoded() const
        {
            return instruction;
        }

        /// @brief 
        /// @param op 
        /// @return 
        constexpr Instruction& set_opcode(Opcode op)
        {
            instruction |= static_cast<std::uint16_t>(op);
            return *this;
        }

        /// @brief 
        /// @param imm 
        /// @return 
        constexpr Instruction& set_imm4(std::uint8_t imm)
        {
            instruction |= static_cast<std::uint16_t>(imm & 0x0F) << 4;
            return *this;
        }

        /// @brief 
        /// @param imm 
        /// @return 
        constexpr Instruction& set_imm8(std::uint8_t imm)
        {
            instruction |= static_cast<std::uint16_t>(imm) << 4;
            return *this;
        }

        /// @brief 
        /// @param imm 
        /// @return 
        constexpr Instruction& set_imm12(std::uint16_t imm)
        {
            instruction |= imm & 0x0FFF;
            return *this;
        }

        /// @brief 
        /// @param reg 
        /// @return 
        constexpr Instruction& set_reg1(RegisterId reg)
        {
            instruction |= reg.number();
            return *this;
        }

        /// @brief 
        /// @param reg 
        /// @return 
        constexpr Instruction& set_reg2(RegisterId reg)
        {
            instruction |= reg.number() << 4;
            return *this;
        }

        /// @brief 
        /// @return 
        static constexpr Instruction nop()
        {
            return Instruction()
                .set_opcode(Opcode::MOV_R_R)
                .set_reg1(RegisterId(0))
                .set_reg2(RegisterId(0));
        }

    private:
        std::uint16_t instruction = 0;
    };

}
