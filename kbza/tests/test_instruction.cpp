#include <catch2/catch_test_macros.hpp>

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

    // TODO: MORE TESTS!
}
