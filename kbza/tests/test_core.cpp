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

        core.step();

        REQUIRE(core.get(Kbza::RegisterId::ProgramCounter) == start_value + delta * 2);
    }
}
