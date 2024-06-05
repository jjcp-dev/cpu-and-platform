#include <Catch2/catch_all.hpp>

import Utils;

TEST_CASE("Utils::align()")
{
    SECTION("1 byte alignment")
    {
        std::uint32_t num = GENERATE(range(0, 2048));

        REQUIRE(Utils::align<1>(num) == num);
    }

    SECTION("2 byte alignment")
    {
        std::uint32_t num = GENERATE(range(0, 1024));

        REQUIRE(Utils::align<2>(num * 2 + 0) == num * 2);
        REQUIRE(Utils::align<2>(num * 2 + 1) == num * 2);
    }

    SECTION("4 byte alignment")
    {
        std::uint32_t num = GENERATE(range(0, 512));

        REQUIRE(Utils::align<4>(num * 4 + 0) == num * 4);
        REQUIRE(Utils::align<4>(num * 4 + 1) == num * 4);
        REQUIRE(Utils::align<4>(num * 4 + 2) == num * 4);
        REQUIRE(Utils::align<4>(num * 4 + 3) == num * 4);
    }

    SECTION("8 byte alignment")
    {
        std::uint32_t num = GENERATE(range(0, 256));

        REQUIRE(Utils::align<8>(num * 8 + 0) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 1) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 2) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 3) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 4) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 5) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 6) == num * 8);
        REQUIRE(Utils::align<8>(num * 8 + 7) == num * 8);
    }

    SECTION("16 byte alignment")
    {
        std::uint32_t num = GENERATE(range(0, 128));

        REQUIRE(Utils::align<16>(num * 16 +  0) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  1) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  2) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  3) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  4) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  5) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  6) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  7) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  8) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 +  9) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 + 10) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 + 12) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 + 13) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 + 14) == num * 16);
        REQUIRE(Utils::align<16>(num * 16 + 15) == num * 16);
    }
}
