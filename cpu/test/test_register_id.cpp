#include <catch2/catch_test_macros.hpp>

import Cpu;

using namespace Cpu;

TEST_CASE("Cpu::RegisterId")
{
    REQUIRE(RegisterId(0).number() == 0);
    REQUIRE(RegisterId(1).number() == 1);
    REQUIRE(RegisterId(2).number() == 2);
    REQUIRE(RegisterId(3).number() == 3);
    REQUIRE(RegisterId(4).number() == 4);
    REQUIRE(RegisterId(5).number() == 5);
    REQUIRE(RegisterId(6).number() == 6);
    REQUIRE(RegisterId(7).number() == 7);
    REQUIRE(RegisterId(8).number() == 8);
    REQUIRE(RegisterId(9).number() == 9);
    REQUIRE(RegisterId(10).number() == 10);
    REQUIRE(RegisterId(11).number() == 11);
    REQUIRE(RegisterId(12).number() == 12);
    REQUIRE(RegisterId(13).number() == 13);
    REQUIRE(RegisterId(14).number() == 14);
    REQUIRE(RegisterId(15).number() == 15);

    REQUIRE(RegisterId(16).number() == 0);
    REQUIRE(RegisterId(17).number() == 1);
    REQUIRE(RegisterId(18).number() == 2);
    REQUIRE(RegisterId(19).number() == 3);
    REQUIRE(RegisterId(20).number() == 4);
    REQUIRE(RegisterId(21).number() == 5);

    REQUIRE(RegisterId(255).number() == 15);

    SECTION("Equality operators")
    {
        REQUIRE(RegisterId(0) == RegisterId(0));
        REQUIRE(RegisterId(0) == RegisterId(16));

        REQUIRE(RegisterId(1) == RegisterId(1));
        REQUIRE(RegisterId(1) == RegisterId(17));

        REQUIRE(RegisterId(2) != RegisterId(1));
        REQUIRE(RegisterId(2) != RegisterId(17));
    }
}
