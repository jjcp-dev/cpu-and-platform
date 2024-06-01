#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <bit>
#include <vector>

import Kbza;

TEST_CASE("Kbza::MemoryController")
{
    SECTION("Create with a properly aligned buffer")
    {
        std::vector<std::uint64_t> mem;
        mem.resize(16);

        auto m = Kbza::MemoryController::create(std::span<std::uint64_t>{ mem });

        REQUIRE(m.has_value());
    }

    SECTION("Create with unaligned buffer")
    {
        std::vector<std::uint8_t> mem;
        mem.resize(16);

        auto m = Kbza::MemoryController::create(std::span{ mem.begin() + 1,
                                                           mem.end() });

        REQUIRE(not m.has_value());
    }

    SECTION("Reads")
    {
        if constexpr (std::endian::native == std::endian::little)
        {
            std::vector<std::uint64_t> mem;

            mem.push_back(0x0001'0203'0405'0607);
            mem.push_back(0x0809'0A0B'0C0D'0E0F);
            mem.push_back(0x1011'1213'1415'1617);
            mem.push_back(0x1819'1A1B'1C1D'1E1F);

            auto m = Kbza::MemoryController::create(std::span<std::uint64_t>{ mem }).value();

            REQUIRE(m.read<std::uint8_t>(Kbza::Address<1>::create_aligned(0)) == 0x07);
            REQUIRE(m.read<std::uint8_t>(Kbza::Address<1>::create_aligned(10)) == 0x0D);

            REQUIRE(m.read<std::uint16_t>(Kbza::Address<2>::create_aligned(0)) == 0x0607);
            REQUIRE(m.read<std::uint16_t>(Kbza::Address<2>::create_aligned(25)) == 0x1E1F);

            REQUIRE(m.read<std::uint32_t>(Kbza::Address<4>::create_aligned(0)) == 0x0405'0607);
            REQUIRE(m.read<std::uint32_t>(Kbza::Address<4>::create_aligned(15)) == 0x0809'0A0B);

            REQUIRE(m.read<std::uint64_t>(Kbza::Address<8>::create_aligned(0)) == 0x0001'0203'0405'0607);
            REQUIRE(m.read<std::uint64_t>(Kbza::Address<8>::create_aligned(24)) == 0x1819'1A1B'1C1D'1E1F);
        }
        else
        {
            REQUIRE(false);
        }
    }

    SECTION("Writes")
    {
        std::vector<std::uint64_t> mem;

        mem.push_back(0x0001'0203'0405'0607);
        mem.push_back(0x0809'0A0B'0C0D'0E0F);
        mem.push_back(0x1011'1213'1415'1617);
        mem.push_back(0x1819'1A1B'1C1D'1E1F);

        auto m = Kbza::MemoryController::create(std::span<std::uint64_t>{ mem }).value();

        m.write<std::uint8_t>(Kbza::Address<1>::create_aligned(2), 0xAB);
        REQUIRE(m.read<std::uint8_t>(Kbza::Address<1>::create_aligned(2)) == 0xAB);

        m.write<std::uint16_t>(Kbza::Address<2>::create_aligned(6), 0xABCD);
        REQUIRE(m.read<std::uint16_t>(Kbza::Address<2>::create_aligned(6)) == 0xABCD);

        m.write<std::uint32_t>(Kbza::Address<4>::create_aligned(0), 0xABCD'EF01);
        REQUIRE(m.read<std::uint32_t>(Kbza::Address<4>::create_aligned(0)) == 0xABCD'EF01);

        m.write<std::uint64_t>(Kbza::Address<8>::create_aligned(16), 0xABCD'EF01'0203'0405);
        REQUIRE(m.read<std::uint64_t>(Kbza::Address<8>::create_aligned(16)) == 0xABCD'EF01'0203'0405);
    }

    SECTION("Copy")
    {
        REQUIRE(false);
    }
}
