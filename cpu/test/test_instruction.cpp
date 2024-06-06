#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

import Cpu;

using namespace Cpu;

TEST_CASE("Cpu::Instruction")
{
    SECTION("Default constructor")
    {
        const auto i = Instruction();

        REQUIRE(i.opcode() == Opcode::MOV_R_I8);
        REQUIRE(i.encoded() == 0);
        REQUIRE(i.imm8() == 0);
        REQUIRE(i.reg1() == 0);
    }

    SECTION("nop() helper")
    {
        const auto i = Instruction::nop();

        REQUIRE(i.opcode() == Opcode::MOV_R_R);
        REQUIRE(i.encoded() == 0xA300);
        REQUIRE(i.reg1() == 0);
        REQUIRE(i.reg2() == 0);
    }

    SECTION("XXX_R_I8")
    {
        auto opcode = GENERATE(Opcode::MOV_R_I8, 
                               Opcode::MOVS_R_I8);

        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(range(0, 256));

        const auto i = Instruction().set_opcode(opcode)
                                          .set_reg1(RegisterId(reg))
                                          .set_imm8(num);

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg);
        REQUIRE(i.imm8() == num);
    }

    SECTION("XXX_I12")
    {
        SECTION("Unsigned")
        {
            auto opcode = GENERATE(Opcode::CALL_I12, 
                                   Opcode::JMP_I12);

            auto num = GENERATE(range(0, 4096));

            const auto i = Instruction().set_opcode(opcode)
                                              .set_imm12(num);

            REQUIRE(i.opcode() == opcode);
            REQUIRE(i.imm12() == num);
        }

        SECTION("Signed")
        {
            auto opcode = GENERATE(Opcode::CALL_I12, 
                                   Opcode::JMP_I12);

            auto num = GENERATE(range(-2048, 2047));

            const auto i = Instruction().set_opcode(opcode)
                                              .set_imm12(num);

            REQUIRE(i.opcode() == opcode);
            REQUIRE(i.signed_imm12() == num);
        }
    }

    SECTION("XXX_R_I4")
    {
        auto opcode = GENERATE(
            Opcode::LSHL0_R_I4,
            Opcode::LSHL1_R_I4,
            Opcode::LSHL2_R_I4,
            Opcode::LSHL3_R_I4,
            Opcode::LSHR0_R_I4,
            Opcode::LSHR1_R_I4,
            Opcode::LSHR2_R_I4,
            Opcode::LSHR3_R_I4
        );

        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(range(0, 16));

        const auto i = Instruction().set_opcode(opcode)
                                          .set_reg1(RegisterId(reg))
                                          .set_imm4(num);

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg);
        REQUIRE(i.imm4() == num);
    }

    SECTION("XXX_R")
    {
        auto opcode = GENERATE(
            Opcode::PUSH_R,
            Opcode::POP_R,
            Opcode::JMP_R,
            Opcode::CALL_R,
            Opcode::MOV_R_I16,
            Opcode::MOV_R_I32,
            Opcode::MOV_R_I64,
            Opcode::MOVS_R_I16,
            Opcode::MOVS_R_I32
        );

        auto reg = GENERATE(range(0, 16));

        const auto i = Instruction().set_opcode(opcode)
                                          .set_reg1(RegisterId(reg));

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg);
    }

    SECTION("XXX_R_R")
    {
        auto opcode = GENERATE(
            Opcode::SWP_R_R,
            Opcode::MOV_R_R,
            Opcode::MOVS_R_R8,
            Opcode::MOVS_R_R16,
            Opcode::MOVS_R_R32,
            Opcode::MOV_R_M8,
            Opcode::MOV_R_M16,
            Opcode::MOV_R_M32,
            Opcode::MOV_R_M64,
            Opcode::MOVS_R_M8,
            Opcode::MOVS_R_M16,
            Opcode::MOVS_R_M32,
            Opcode::MOV_M8_R,
            Opcode::MOV_M16_R,
            Opcode::MOV_M32_R,
            Opcode::MOV_M64_R,
            Opcode::AND_R_R,
            Opcode::OR_R_R,
            Opcode::XOR_R_R,
            Opcode::TEST_R_R,
            Opcode::ADD_R_R,
            Opcode::SUB_R_R,
            Opcode::ADDC_R_R,
            Opcode::SUBC_R_R
        );

        auto reg1 = GENERATE(range(0, 16));
        auto reg2 = GENERATE(range(0, 16));

        const auto i = Instruction().set_opcode(opcode)
                                          .set_reg1(RegisterId(reg1))
                                          .set_reg2(RegisterId(reg2));

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg1);
        REQUIRE(i.reg2() == reg2);
    }

    SECTION("XXX")
    {
        auto opcode = GENERATE(
            Opcode::RET,
            Opcode::STI,
            Opcode::CLI,
            Opcode::CPUID,
            Opcode::HALT
        );

        const auto i = Instruction().set_opcode(opcode);

        REQUIRE(i.opcode() == opcode);
    }
}
