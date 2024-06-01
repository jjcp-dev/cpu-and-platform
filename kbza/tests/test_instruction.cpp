#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

import Kbza;

TEST_CASE("Kbza::Instruction")
{
    SECTION("Default constructor")
    {
        const auto i = Kbza::Instruction();

        REQUIRE(i.opcode() == Kbza::Opcode::MOV_R_I8);
        REQUIRE(i.encoded() == 0);
        REQUIRE(i.imm8() == 0);
        REQUIRE(i.reg1() == 0);
    }

    SECTION("nop() helper")
    {
        const auto i = Kbza::Instruction::nop();

        REQUIRE(i.opcode() == Kbza::Opcode::MOV_R_R);
        REQUIRE(i.encoded() == 0xA300);
        REQUIRE(i.reg1() == 0);
        REQUIRE(i.reg2() == 0);
    }

    SECTION("XXX_R_I8")
    {
        auto opcode = GENERATE(Kbza::Opcode::MOV_R_I8, 
                               Kbza::Opcode::MOVS_R_I8);

        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(range(0, 256));

        const auto i = Kbza::Instruction().set_opcode(opcode)
                                          .set_reg1(Kbza::RegisterId(reg))
                                          .set_imm8(num);

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg);
        REQUIRE(i.imm8() == num);
    }

    SECTION("XXX_I12")
    {
        SECTION("Unsigned")
        {
            auto opcode = GENERATE(Kbza::Opcode::CALL_I12, 
                                   Kbza::Opcode::JMP_I12);

            auto num = GENERATE(range(0, 4096));

            const auto i = Kbza::Instruction().set_opcode(opcode)
                                              .set_imm12(num);

            REQUIRE(i.opcode() == opcode);
            REQUIRE(i.imm12() == num);
        }

        SECTION("Signed")
        {
            auto opcode = GENERATE(Kbza::Opcode::CALL_I12, 
                                   Kbza::Opcode::JMP_I12);

            auto num = GENERATE(range(-2048, 2047));

            const auto i = Kbza::Instruction().set_opcode(opcode)
                                              .set_imm12(num);

            REQUIRE(i.opcode() == opcode);
            REQUIRE(i.signed_imm12() == num);
        }
    }

    SECTION("XXX_R_I4")
    {
        auto opcode = GENERATE(
            Kbza::Opcode::LSHL0_R_I4,
            Kbza::Opcode::LSHL1_R_I4,
            Kbza::Opcode::LSHR0_R_I4,
            Kbza::Opcode::LSHR1_R_I4
        );

        auto reg = GENERATE(range(0, 16));
        auto num = GENERATE(range(0, 16));

        const auto i = Kbza::Instruction().set_opcode(opcode)
                                          .set_reg1(Kbza::RegisterId(reg))
                                          .set_imm4(num);

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg);
        REQUIRE(i.imm4() == num);
    }

    SECTION("XXX_R")
    {
        auto opcode = GENERATE(
            Kbza::Opcode::PUSH_R,
            Kbza::Opcode::POP_R,
            Kbza::Opcode::JMP_R,
            Kbza::Opcode::CALL_R,
            Kbza::Opcode::MOV_R_I16,
            Kbza::Opcode::MOV_R_I32,
            Kbza::Opcode::MOV_R_I64,
            Kbza::Opcode::MOVS_R_I16,
            Kbza::Opcode::MOVS_R_I32
        );

        auto reg = GENERATE(range(0, 16));

        const auto i = Kbza::Instruction().set_opcode(opcode)
                                          .set_reg1(Kbza::RegisterId(reg));

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg);
    }

    SECTION("XXX_R_R")
    {
        auto opcode = GENERATE(
            Kbza::Opcode::SWP_R_R,
            Kbza::Opcode::MOV_R_R,
            Kbza::Opcode::MOVS_R_R8,
            Kbza::Opcode::MOVS_R_R16,
            Kbza::Opcode::MOVS_R_R32,
            Kbza::Opcode::MOV_R_M8,
            Kbza::Opcode::MOV_R_M16,
            Kbza::Opcode::MOV_R_M32,
            Kbza::Opcode::MOV_R_M64,
            Kbza::Opcode::MOVS_R_M8,
            Kbza::Opcode::MOVS_R_M16,
            Kbza::Opcode::MOVS_R_M32,
            Kbza::Opcode::MOV_M8_R,
            Kbza::Opcode::MOV_M16_R,
            Kbza::Opcode::MOV_M32_R,
            Kbza::Opcode::MOV_M64_R,
            Kbza::Opcode::AND_R_R,
            Kbza::Opcode::OR_R_R,
            Kbza::Opcode::XOR_R_R,
            Kbza::Opcode::TEST_R_R,
            Kbza::Opcode::ADD_R_R,
            Kbza::Opcode::SUB_R_R,
            Kbza::Opcode::ADDC_R_R,
            Kbza::Opcode::SUBC_R_R
        );

        auto reg1 = GENERATE(range(0, 16));
        auto reg2 = GENERATE(range(0, 16));

        const auto i = Kbza::Instruction().set_opcode(opcode)
                                          .set_reg1(Kbza::RegisterId(reg1))
                                          .set_reg2(Kbza::RegisterId(reg2));

        REQUIRE(i.opcode() == opcode);
        REQUIRE(i.reg1() == reg1);
        REQUIRE(i.reg2() == reg2);
    }

    SECTION("XXX")
    {
        auto opcode = GENERATE(
            Kbza::Opcode::RET,
            Kbza::Opcode::STI,
            Kbza::Opcode::CLI,
            Kbza::Opcode::CPUID,
            Kbza::Opcode::HALT
        );

        const auto i = Kbza::Instruction().set_opcode(opcode);

        REQUIRE(i.opcode() == opcode);
    }
}
