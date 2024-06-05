#include <Catch2/catch_all.hpp>

import Utils;

TEST_CASE("Utils::is_power_of_two()")
{
    REQUIRE(Utils::is_power_of_two(0) == false);

    std::uint32_t shift = GENERATE(range(0, 20));

    std::uint32_t start = 1 << shift;
    std::uint32_t end = 1 << (shift + 1);

    REQUIRE(Utils::is_power_of_two(start) == true);

    for (auto i = start + 1; i < end; ++i)
    {
        REQUIRE(Utils::is_power_of_two(i) == false);
    }
}
