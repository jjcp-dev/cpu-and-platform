#include <catch2/catch_test_macros.hpp>

import Kbza;

TEST_CASE("Kbza::RegisterId")
{
    REQUIRE(Kbza::RegisterId(0).number() == 0);
    REQUIRE(Kbza::RegisterId(1).number() == 1);
    REQUIRE(Kbza::RegisterId(2).number() == 2);
    REQUIRE(Kbza::RegisterId(3).number() == 3);
    REQUIRE(Kbza::RegisterId(4).number() == 4);
    REQUIRE(Kbza::RegisterId(5).number() == 5);
    REQUIRE(Kbza::RegisterId(6).number() == 6);
    REQUIRE(Kbza::RegisterId(7).number() == 7);
    REQUIRE(Kbza::RegisterId(8).number() == 8);
    REQUIRE(Kbza::RegisterId(9).number() == 9);
    REQUIRE(Kbza::RegisterId(10).number() == 10);
    REQUIRE(Kbza::RegisterId(11).number() == 11);
    REQUIRE(Kbza::RegisterId(12).number() == 12);
    REQUIRE(Kbza::RegisterId(13).number() == 13);
    REQUIRE(Kbza::RegisterId(14).number() == 14);
    REQUIRE(Kbza::RegisterId(15).number() == 15);

    REQUIRE(Kbza::RegisterId(16).number() == 0);
    REQUIRE(Kbza::RegisterId(17).number() == 1);
    REQUIRE(Kbza::RegisterId(18).number() == 2);
    REQUIRE(Kbza::RegisterId(19).number() == 3);
    REQUIRE(Kbza::RegisterId(20).number() == 4);
    REQUIRE(Kbza::RegisterId(21).number() == 5);

    REQUIRE(Kbza::RegisterId(255).number() == 15);

    SECTION("Equality operators")
    {
        REQUIRE(Kbza::RegisterId(0) == Kbza::RegisterId(0));
        REQUIRE(Kbza::RegisterId(0) == Kbza::RegisterId(16));

        REQUIRE(Kbza::RegisterId(1) == Kbza::RegisterId(1));
        REQUIRE(Kbza::RegisterId(1) == Kbza::RegisterId(17));

        REQUIRE(Kbza::RegisterId(2) != Kbza::RegisterId(1));
        REQUIRE(Kbza::RegisterId(2) != Kbza::RegisterId(17));
    }
}
