#include <Catch2/catch_all.hpp>

import Utils;

TEST_CASE("Utils::is_aligned()")
{
    SECTION("1")
    {
        auto num = GENERATE(range(0, 2048));

        REQUIRE(Utils::is_aligned<1>(num) == true);
    }

    SECTION("2")
    {
        auto num = GENERATE(range(0, 1024));

        REQUIRE(Utils::is_aligned<2>(num * 2 + 0) == true);
        REQUIRE(Utils::is_aligned<2>(num * 2 + 1) == false);
    }

    SECTION("4")
    {
        auto num = GENERATE(range(0, 512));

        REQUIRE(Utils::is_aligned<4>(num * 4 + 0) == true);
        REQUIRE(Utils::is_aligned<4>(num * 4 + 1) == false);
        REQUIRE(Utils::is_aligned<4>(num * 4 + 2) == false);
        REQUIRE(Utils::is_aligned<4>(num * 4 + 3) == false);
    }

    SECTION("8")
    {
        auto num = GENERATE(range(0, 256));

        REQUIRE(Utils::is_aligned<8>(num * 8 + 0) == true);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 1) == false);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 2) == false);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 3) == false);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 4) == false);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 5) == false);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 6) == false);
        REQUIRE(Utils::is_aligned<8>(num * 8 + 7) == false);
    }

    SECTION("16")
    {
        auto num = GENERATE(range(0, 128));

        REQUIRE(Utils::is_aligned<16>(num * 16 +  0) == true);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  1) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  2) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  3) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  4) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  5) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  6) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  7) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  8) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 +  9) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 + 10) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 + 12) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 + 13) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 + 14) == false);
        REQUIRE(Utils::is_aligned<16>(num * 16 + 15) == false);
    }
}
