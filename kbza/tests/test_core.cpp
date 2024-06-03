#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

#include <cstdint>
#include <span>
#include <vector>

import Kbza;


TEST_CASE("Kbza::Core")
{
    std::vector<std::uint64_t> buffer;

    buffer.resize(1024 * 16);

    auto mc = Kbza::MemoryController::create(std::span{ buffer }).value();

    SECTION("MOV_R_I8")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(range(0, 256));

        std::vector<std::uint16_t> program;

        program.push_back(
            Kbza::Instruction().set_opcode(Kbza::Opcode::MOV_R_I8)
                               .set_reg1(Kbza::RegisterId(reg))
                               .set_imm8(num)
                               .encoded());

        mc.copy(0, std::span{ program });

        auto core = Kbza::Core{ mc };

        core.step();

        REQUIRE(core.get(Kbza::RegisterId(reg)) == num);
        REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 2);
    }

    SECTION("MOVS_R_I8")
    {
        auto reg = GENERATE(range(0, 16));

        SECTION("Non negative")
        {
            auto num = GENERATE(range(0, (int)std::numeric_limits<std::int8_t>::max()));

            std::vector<std::uint16_t> program;

            program.push_back(
                Kbza::Instruction().set_opcode(Kbza::Opcode::MOVS_R_I8)
                                   .set_reg1(Kbza::RegisterId(reg))
                                   .set_imm8(num)
                                   .encoded());

            mc.copy(0, std::span{ program });

            auto core = Kbza::Core{ mc };

            core.step();

            REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 2);
            REQUIRE(core.get(Kbza::RegisterId(reg)) == num);
        }

        SECTION("Negative")
        {
            auto num = GENERATE(range((int)std::numeric_limits<std::int8_t>::min(), 0));

            std::vector<std::uint16_t> program;

            program.push_back(
                Kbza::Instruction().set_opcode(Kbza::Opcode::MOVS_R_I8)
                                   .set_reg1(Kbza::RegisterId(reg))
                                   .set_imm8(num)
                                   .encoded());

            mc.copy(0, std::span{ program });

            auto core = Kbza::Core{ mc };

            core.step();

            REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 2);
            REQUIRE(static_cast<std::int64_t>(core.get(Kbza::RegisterId(reg))) == num);
        }
    }

    SECTION("CALL_I12")
    {
        auto delta = GENERATE(range(-2048, 2047));

        std::vector<std::uint16_t> program;

        program.push_back(
            Kbza::Instruction().set_opcode(Kbza::Opcode::CALL_I12)
                               .set_imm12(delta)
                               .encoded());

        const auto start = Kbza::Address<2>::create_aligned(1024 * 16);
        const auto start_value = start.value();

        mc.copy(start.value(), std::span{ program });

        auto core = Kbza::Core{ mc };

        core.set(Kbza::RegisterId::ProgramCounter, start);

        core.step();

        REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == start_value + delta * 2);

        auto sp = Kbza::Address<8>::create_aligned(core.get(Kbza::RegisterId(15)));
        auto top = mc.read<std::uint64_t>(sp);

        REQUIRE(top == (start + 1).value());
    }

    SECTION("JMP_I12")
    {
        auto delta = GENERATE(range(-2048, 2047));

        std::vector<std::uint16_t> program;

        program.push_back(
            Kbza::Instruction().set_opcode(Kbza::Opcode::JMP_I12)
                               .set_imm12(delta)
                               .encoded());

        const auto start = Kbza::Address<2>::create_aligned(1024 * 16);
        const auto start_value = start.value();

        mc.copy(start.value(), std::span{ program });

        auto core = Kbza::Core{ mc };

        core.set(Kbza::RegisterId::ProgramCounter, start);

        auto sp = core.get(Kbza::RegisterId(15));

        core.step();

        REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == start_value + delta * 2);
        REQUIRE(sp == core.get(Kbza::RegisterId(15)));
    }

    SECTION("LSHL{0, 1, 2, 3}_R_I4")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
            0x1234'5678'9ABC'DEF0,
            0x1357'9BDF'2468'ACE0,
            0x2468'ACE0'2468'ACE0,
            0xABCD'EF01'2345'6789,
            0xCAFE'BABE'DEAD'BEEF,
            0xFEDC'BA98'7654'3210,
            0,
            1,
            2,
            3
        );
        auto shift = GENERATE(range(0, 64));

        std::vector<std::uint16_t> program;

        Kbza::Opcode opcode = Kbza::Opcode::LSHL0_R_I4;

        if (shift <= 0x0F)
        {
            opcode = Kbza::Opcode::LSHL0_R_I4;
        }
        else if (shift <= 0x1F)
        {
            opcode = Kbza::Opcode::LSHL1_R_I4;
        }
        else if (shift <= 0x2F)
        {
            opcode = Kbza::Opcode::LSHL2_R_I4;
        }
        else if (shift <= 0x3F)
        {
            opcode = Kbza::Opcode::LSHL3_R_I4;
        }

        program.push_back(
            Kbza::Instruction().set_opcode(opcode)
                               .set_reg1(Kbza::RegisterId(reg))
                               .set_imm4(shift)
                               .encoded());

        mc.copy(0, std::span{ program });

        auto core = Kbza::Core{ mc };

        core.set(Kbza::RegisterId(reg), num);
        core.step();

        REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 2);
        REQUIRE(core.get(Kbza::RegisterId(reg)) == static_cast<std::uint64_t>(num) << shift);
    }

    SECTION("LSHR{0, 1, 2, 3}_R_I4")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
            0x1234'5678'9ABC'DEF0,
            0x1357'9BDF'2468'ACE0,
            0x2468'ACE0'2468'ACE0,
            0xABCD'EF01'2345'6789,
            0xCAFE'BABE'DEAD'BEEF,
            0xFEDC'BA98'7654'3210,
            0,
            1,
            2,
            3
        );
        auto shift = GENERATE(range(0, 64));

        std::vector<std::uint16_t> program;

        Kbza::Opcode opcode = Kbza::Opcode::LSHR0_R_I4;

        if (shift <= 0x0F)
        {
            opcode = Kbza::Opcode::LSHR0_R_I4;
        }
        else if (shift <= 0x1F)
        {
            opcode = Kbza::Opcode::LSHR1_R_I4;
        }
        else if (shift <= 0x2F)
        {
            opcode = Kbza::Opcode::LSHR2_R_I4;
        }
        else if (shift <= 0x3F)
        {
            opcode = Kbza::Opcode::LSHR3_R_I4;
        }

        program.push_back(
            Kbza::Instruction().set_opcode(opcode)
                               .set_reg1(Kbza::RegisterId(reg))
                               .set_imm4(shift)
                               .encoded());

        mc.copy(0, std::span{ program });

        auto core = Kbza::Core{ mc };

        core.set(Kbza::RegisterId(reg), num);
        core.step();

        REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 2);
        REQUIRE(core.get(Kbza::RegisterId(reg)) == static_cast<std::uint64_t>(num) >> shift);
    }

    SECTION("PUSH_R / POP_R")
    {
        auto reg1 = GENERATE(range(0, 16));
        auto reg2 = GENERATE(range(0, 16));

        auto numbers = std::vector<std::uint64_t>{ { 
            0x7A2F'9B8E'3C4D'5A1B,
            0x2E6C'3D9A'5B1F'8F0D,
            0x9D0B'4E7F'6A3C'8E2F,
            0x5F8C'1A3B'6E9D'2D4C,
            0x3B4D'9E2F'1A5C'8C0E,
            0x8E1B'5A3C'4D9E'2F6C,
            0x6C3D'8E2F'1B4D'9A5F,
            0x4E7F'6A3C'8E2F'1A5C,
            0x1A3B'6E9D'2D4C'8E2F,
            0x9E2F'1A5C'8C0E'3B4D 
        } };

        for (auto num : numbers)
        {
            auto core = Kbza::Core{ mc };

            core.set(Kbza::RegisterId(reg1), num);
            core.set(Kbza::RegisterId(reg2), 0);

            std::vector<std::uint16_t> program;

            program.push_back(
                Kbza::Instruction().set_opcode(Kbza::Opcode::PUSH_R)
                                   .set_reg1(Kbza::RegisterId(reg1))
                                   .encoded());

            program.push_back(
                Kbza::Instruction().set_opcode(Kbza::Opcode::POP_R)
                                   .set_reg1(Kbza::RegisterId(reg2))
                                   .encoded());

            mc.copy(0, std::span{ program });

            core.step();

            REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 2);

            auto sp = Kbza::Address<8>::create_aligned(core.get(Kbza::RegisterId(15)));
            auto top = mc.read<std::uint64_t>(sp);

            // REQUIRE(top == num);

            core.step();

            REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == 4);
            REQUIRE(core.get(Kbza::RegisterId(reg2)) == num);
        }
    }
}