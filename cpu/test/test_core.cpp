#include <catch2/catch_all.hpp>

#include <cstdint>
#include <span>
#include <vector>

import Cpu;
import Platform;
import Utils;

using namespace Cpu;

using Platform::MemoryController;
using Utils::Address;


TEST_CASE("Cpu::Core")
{
    std::vector<std::uint64_t> buffer;

    buffer.resize(1024 * 16);

    auto mc = MemoryController::create(std::span{ buffer }).value();

    SECTION("MOV_R_I8")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(range(0, 256));

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::MOV_R_I8)
                               .set_reg1(RegisterId(reg))
                               .set_imm8(num)
                               .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.step();

        REQUIRE(core.get(RegisterId(reg)) == num);
        REQUIRE(core.get(RegisterId::ProgramCounter) == 2);
    }

    SECTION("MOVS_R_I8")
    {
        auto reg = GENERATE(range(0, 16));

        SECTION("Non negative")
        {
            auto num = GENERATE(range(0, (int)std::numeric_limits<std::int8_t>::max()));

            std::vector<std::uint16_t> program;

            program.push_back(
                Instruction().set_opcode(Opcode::MOVS_R_I8)
                                   .set_reg1(RegisterId(reg))
                                   .set_imm8(num)
                                   .encoded());

            mc.copy(std::span{ program }, 0);

            auto core = Core{ mc };

            core.step();

            REQUIRE(core.get(RegisterId::ProgramCounter) == 2);
            REQUIRE(core.get(RegisterId(reg)) == num);
        }

        SECTION("Negative")
        {
            auto num = GENERATE(range((int)std::numeric_limits<std::int8_t>::min(), 0));

            std::vector<std::uint16_t> program;

            program.push_back(
                Instruction().set_opcode(Opcode::MOVS_R_I8)
                                   .set_reg1(RegisterId(reg))
                                   .set_imm8(num)
                                   .encoded());

            mc.copy(std::span{ program }, 0);

            auto core = Core{ mc };

            core.step();

            REQUIRE(core.get(RegisterId::ProgramCounter) == 2);
            REQUIRE(static_cast<std::int64_t>(core.get(RegisterId(reg))) == num);
        }
    }

    SECTION("CALL_I12")
    {
        auto delta = GENERATE(range(-2048, 2047));

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::CALL_I12)
                               .set_imm12(delta)
                               .encoded());

        const auto start = Address<2>::create_aligned(1024 * 16);
        const auto start_value = start.value();

        mc.copy(std::span{ program }, start.value());

        auto core = Core{ mc };

        core.set(RegisterId::ProgramCounter, start);

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == start_value + delta * 2);

        auto sp = Address<8>::create_aligned(core.get(RegisterId(15)));
        auto top = mc.read<std::uint64_t>(sp);

        REQUIRE(top == (start + 1).value());
    }

    SECTION("JMP_I12")
    {
        auto delta = GENERATE(range(-2048, 2047));

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::JMP_I12)
                               .set_imm12(delta)
                               .encoded());

        const auto start = Address<2>::create_aligned(1024 * 16);
        const auto start_value = start.value();

        mc.copy(std::span{ program }, start.value());

        auto core = Core{ mc };

        core.set(RegisterId::ProgramCounter, start);

        auto sp = core.get(RegisterId(15));

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == start_value + delta * 2);
        REQUIRE(sp == core.get(RegisterId(15)));
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

        Opcode opcode = Opcode::LSHL0_R_I4;

        if (shift <= 0x0F)
        {
            opcode = Opcode::LSHL0_R_I4;
        }
        else if (shift <= 0x1F)
        {
            opcode = Opcode::LSHL1_R_I4;
        }
        else if (shift <= 0x2F)
        {
            opcode = Opcode::LSHL2_R_I4;
        }
        else if (shift <= 0x3F)
        {
            opcode = Opcode::LSHL3_R_I4;
        }

        program.push_back(
            Instruction().set_opcode(opcode)
                               .set_reg1(RegisterId(reg))
                               .set_imm4(shift)
                               .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.set(RegisterId(reg), num);
        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 2);
        REQUIRE(core.get(RegisterId(reg)) == static_cast<std::uint64_t>(num) << shift);
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

        Opcode opcode = Opcode::LSHR0_R_I4;

        if (shift <= 0x0F)
        {
            opcode = Opcode::LSHR0_R_I4;
        }
        else if (shift <= 0x1F)
        {
            opcode = Opcode::LSHR1_R_I4;
        }
        else if (shift <= 0x2F)
        {
            opcode = Opcode::LSHR2_R_I4;
        }
        else if (shift <= 0x3F)
        {
            opcode = Opcode::LSHR3_R_I4;
        }

        program.push_back(
            Instruction().set_opcode(opcode)
                               .set_reg1(RegisterId(reg))
                               .set_imm4(shift)
                               .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.set(RegisterId(reg), num);
        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 2);
        REQUIRE(core.get(RegisterId(reg)) == static_cast<std::uint64_t>(num) >> shift);
    }

    SECTION("PUSH_R / POP_R")
    {
        auto reg1 = GENERATE(range(0, 15)); // Skip SP
        auto reg2 = GENERATE(range(0, 15)); // Skip SP
        auto num = GENERATE(
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
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::PUSH_R)
                               .set_reg1(RegisterId(reg1))
                               .encoded());

        program.push_back(
            Instruction().set_opcode(Opcode::POP_R)
                               .set_reg1(RegisterId(reg2))
                               .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.set(RegisterId(reg1), num);
        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 2);

        auto sp = Address<8>::create_aligned(core.get(RegisterId(15)));
        auto top = mc.read<std::uint64_t>(sp);

        REQUIRE(top == num);

        core.set(RegisterId(reg2), 0);
        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 4);
        REQUIRE(core.get(RegisterId(reg2)) == num);
        REQUIRE(core.get(RegisterId(15)) == (sp + 1).value());
    }

    SECTION("CALL_R")
    {
        auto reg = GENERATE(range(0, 15));
        auto address = GENERATE(
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
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::CALL_R)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.set(RegisterId(reg), address);

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == Utils::align<2>(address));

        auto sp = Address<8>::create_aligned(core.get(RegisterId::stack()));
        auto top = mc.read<std::uint64_t>(sp);

        REQUIRE(top == 2);
    }

    SECTION("CALL_R (`call sp`)")
    {
        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::CALL_R)
                         .set_reg1(RegisterId::stack())
                         .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.set(RegisterId::stack(), 1024 + 8);

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 1024);

        auto sp = Address<8>::create_aligned(core.get(RegisterId::stack()));
        auto top = mc.read<std::uint64_t>(sp);

        REQUIRE(top == 2);
    }

    SECTION("JMP_R")
    {
        auto reg = GENERATE(range(0, 16));
        auto address = GENERATE(
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
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::JMP_R)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.set(RegisterId(reg), address);

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == Utils::align<2>(address));
    }

    SECTION("MOV_R_I16")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
            0x3C4D,
            0x5B1F,
            0x6A3C,
            0x6E9D,
            0x1A5C,
            0x4D9E,
            0x1B4D,
            0x8E2F,
            0x2D4C,
            0x8C0E 
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::MOV_R_I16)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        program.push_back(num);

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 4);
        REQUIRE(core.get(RegisterId(reg)) == num);
    }

    SECTION("MOV_R_I32 (4byte-aligned instruction)")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
            0x3C4D'5A1B,
            0x5B1F'8F0D,
            0x6A3C'8E2F,
            0x6E9D'2D4C,
            0x1A5C'8C0E,
            0x4D9E'2F6C,
            0x1B4D'9A5F,
            0x8E2F'1A5C,
            0x2D4C'8E2F,
            0x8C0E'3B4D 
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::MOV_R_I32)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        program.push_back(0);

        program.push_back(num & 0x0000FFFF); 
        program.push_back(num >> 16); 

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 8);
        REQUIRE(core.get(RegisterId(reg)) == (unsigned)num);
    }

    SECTION("MOV_R_I32 (Non 4byte-aligned instruction)")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
            0x3C4D'5A1B,
            0x5B1F'8F0D,
            0x6A3C'8E2F,
            0x6E9D'2D4C,
            0x1A5C'8C0E,
            0x4D9E'2F6C,
            0x1B4D'9A5F,
            0x8E2F'1A5C,
            0x2D4C'8E2F,
            0x8C0E'3B4D 
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::MOV_R_I32)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        program.push_back(num & 0x0000FFFF); 
        program.push_back(num >> 16); 

        mc.copy(std::span{ program }, 2);

        auto core = Core{ mc };

        core.set(RegisterId::ProgramCounter, Address<2>::create_aligned(2));

        core.step();

        REQUIRE(core.get(RegisterId(reg)) == (unsigned)num);
        REQUIRE(core.get(RegisterId::ProgramCounter) == 8);
    }

    SECTION("MOV_R_I64 (4byte-aligned instruction)")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
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
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::MOV_R_I64)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        program.push_back(0);

        program.push_back(num >> 0); 
        program.push_back(num >> 16); 
        program.push_back(num >> 32); 
        program.push_back(num >> 48); 

        mc.copy(std::span{ program }, 0);

        auto core = Core{ mc };

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 12);
        REQUIRE(core.get(RegisterId(reg)) == num);
    }

    SECTION("MOV_R_I64 (Non 4byte-aligned instruction)")
    {
        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(
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
        );

        std::vector<std::uint16_t> program;

        program.push_back(
            Instruction().set_opcode(Opcode::MOV_R_I64)
                         .set_reg1(RegisterId(reg))
                         .encoded());

        program.push_back(num >> 0); 
        program.push_back(num >> 16); 
        program.push_back(num >> 32); 
        program.push_back(num >> 48); 

        mc.copy(std::span{ program }, 2);

        auto core = Core{ mc };

        core.set(RegisterId::ProgramCounter, Address<2>::create_aligned(2));

        core.step();

        REQUIRE(core.get(RegisterId::ProgramCounter) == 12);
        REQUIRE(core.get(RegisterId(reg)) == num);
    }

    SECTION("MOVS_R_I16")
    {
    }

    SECTION("MOVS_R_I32")
    {
    }

    SECTION("SWP_R_R")
    {
    }

    SECTION("MOV_R_R")
    {
    }

    SECTION("MOVS_R_R8")
    {
    }

    SECTION("MOVS_R_R16")
    {
    }

    SECTION("MOVS_R_R32")
    {
    }

    SECTION("MOV_M8_R")
    {
    }

    SECTION("MOV_M16_R")
    {
    }

    SECTION("MOV_M32_R")
    {
    }

    SECTION("MOV_M64_R")
    {
    }

    SECTION("AND_R_R")
    {
    }

    SECTION("OR_R_R")
    {
    }

    SECTION("XOR_R_R")      
    {
    }

    SECTION("TEST_R_R")     
    {
    }

    SECTION("ADD_R_R")      
    {
    }

    SECTION("SUB_R_R")      
    {
    }

    SECTION("ADDC_R_R")     
    {
    }

    SECTION("SUBC_R_R")     
    {
    }

    SECTION("RET")          
    {
    }

    SECTION("STI")          
    {
    }

    SECTION("CLI")          
    {
    }

    SECTION("CALL_I16")     
    {
    }

    SECTION("CALL_I32")     
    {
    }

    SECTION("JMP_I16")      
    {
    }

    SECTION("JMP_I32")      
    {
    }

    SECTION("CPUID")        
    {
    }

    SECTION("HALT")         
    {
    }

}
