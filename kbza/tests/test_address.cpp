#include <catch2/catch_test_macros.hpp>

import Kbza;

// FIXME: Needs compilation-failure tests!

TEST_CASE("Kbza::Address")
{
    SECTION("Default constructor")
    {
        REQUIRE(Kbza::Address<1>().value() == 0);
        REQUIRE(Kbza::Address<2>().value() == 0);
        REQUIRE(Kbza::Address<4>().value() == 0);
        REQUIRE(Kbza::Address<8>().value() == 0);
        REQUIRE(Kbza::Address<16>().value() == 0);
    }

    SECTION("Create aligned")
    {
        REQUIRE(Kbza::Address<1>::create_aligned(0).value() == 0);
        REQUIRE(Kbza::Address<1>::create_aligned(1).value() == 1);
        REQUIRE(Kbza::Address<1>::create_aligned(2).value() == 2);
        REQUIRE(Kbza::Address<1>::create_aligned(3).value() == 3);
        REQUIRE(Kbza::Address<1>::create_aligned(4).value() == 4);

        REQUIRE(Kbza::Address<2>::create_aligned(0).value() == 0);
        REQUIRE(Kbza::Address<2>::create_aligned(1).value() == 0);
        REQUIRE(Kbza::Address<2>::create_aligned(2).value() == 2);
        REQUIRE(Kbza::Address<2>::create_aligned(3).value() == 2);
        REQUIRE(Kbza::Address<2>::create_aligned(4).value() == 4);

        REQUIRE(Kbza::Address<4>::create_aligned(0).value() == 0);
        REQUIRE(Kbza::Address<4>::create_aligned(1).value() == 0);
        REQUIRE(Kbza::Address<4>::create_aligned(2).value() == 0);
        REQUIRE(Kbza::Address<4>::create_aligned(3).value() == 0);
        REQUIRE(Kbza::Address<4>::create_aligned(4).value() == 4);
        REQUIRE(Kbza::Address<4>::create_aligned(5).value() == 4);
        REQUIRE(Kbza::Address<4>::create_aligned(6).value() == 4);
        REQUIRE(Kbza::Address<4>::create_aligned(7).value() == 4);
        REQUIRE(Kbza::Address<4>::create_aligned(8).value() == 8);
        REQUIRE(Kbza::Address<4>::create_aligned(9).value() == 8);

        REQUIRE(Kbza::Address<8>::create_aligned(0).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(1).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(2).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(3).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(4).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(5).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(6).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(7).value() == 0);
        REQUIRE(Kbza::Address<8>::create_aligned(8).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(9).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(10).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(11).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(12).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(12).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(13).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(14).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(15).value() == 8);
        REQUIRE(Kbza::Address<8>::create_aligned(16).value() == 16);
        REQUIRE(Kbza::Address<8>::create_aligned(17).value() == 16);
    }

    SECTION("Create")
    {
        REQUIRE(Kbza::Address<1>::create(0).value().value() == 0);
        REQUIRE(Kbza::Address<1>::create(1).value().value() == 1);
        REQUIRE(Kbza::Address<1>::create(2).value().value() == 2);
        REQUIRE(Kbza::Address<1>::create(3).value().value() == 3);
        REQUIRE(Kbza::Address<1>::create(4).value().value() == 4);

        REQUIRE(Kbza::Address<2>::create(0).value().value() == 0);
        REQUIRE(Kbza::Address<2>::create(1).has_value() == false);
        REQUIRE(Kbza::Address<2>::create(2).value().value() == 2);
        REQUIRE(Kbza::Address<2>::create(3).has_value() == false);
        REQUIRE(Kbza::Address<2>::create(4).value().value() == 4);

        REQUIRE(Kbza::Address<4>::create(0).value().value() == 0);
        REQUIRE(Kbza::Address<4>::create(1).has_value() == false);
        REQUIRE(Kbza::Address<4>::create(2).has_value() == false);
        REQUIRE(Kbza::Address<4>::create(3).has_value() == false);
        REQUIRE(Kbza::Address<4>::create(4).value().value() == 4);
        REQUIRE(Kbza::Address<4>::create(5).has_value() == false);
        REQUIRE(Kbza::Address<4>::create(6).has_value() == false);
        REQUIRE(Kbza::Address<4>::create(7).has_value() == false);
        REQUIRE(Kbza::Address<4>::create(8).value().value() == 8);
        REQUIRE(Kbza::Address<4>::create(9).has_value() == false);

        REQUIRE(Kbza::Address<8>::create(0).value().value() == 0);
        REQUIRE(Kbza::Address<8>::create(1).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(2).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(3).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(4).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(5).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(6).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(7).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(8).value().value() == 8);
        REQUIRE(Kbza::Address<8>::create(9).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(10).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(11).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(12).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(12).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(13).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(14).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(15).has_value() == false);
        REQUIRE(Kbza::Address<8>::create(16).value().value() == 16);
        REQUIRE(Kbza::Address<8>::create(17).has_value() == false);
    }

    SECTION("Copy from equal/over aligned Address")
    {
        {
            auto x = Kbza::Address<1>::create_aligned(1024);
            x = Kbza::Address<1>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<2>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<4>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<8>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<16>::create_aligned(32);
            REQUIRE(x.value() == 32);
        }

        {
            auto x = Kbza::Address<2>::create_aligned(1024);
            x = Kbza::Address<2>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<4>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<8>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<16>::create_aligned(32);
            REQUIRE(x.value() == 32);
        }

        {
            auto x = Kbza::Address<4>::create_aligned(1024);
            x = Kbza::Address<4>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<8>::create_aligned(32);
            REQUIRE(x.value() == 32);

            x = Kbza::Address<16>::create_aligned(32);
            REQUIRE(x.value() == 32);
        }
    }

    SECTION("Construct from equal/over aligned Address")
    {
        REQUIRE(Kbza::Address<1>(Kbza::Address<1>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<1>(Kbza::Address<2>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<1>(Kbza::Address<4>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<1>(Kbza::Address<8>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<1>(Kbza::Address<16>::create_aligned(32)).value() == 32);

        REQUIRE(Kbza::Address<2>(Kbza::Address<2>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<2>(Kbza::Address<4>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<2>(Kbza::Address<8>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<2>(Kbza::Address<16>::create_aligned(32)).value() == 32);

        REQUIRE(Kbza::Address<4>(Kbza::Address<4>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<4>(Kbza::Address<8>::create_aligned(32)).value() == 32);
        REQUIRE(Kbza::Address<4>(Kbza::Address<16>::create_aligned(32)).value() == 32);
    }

    SECTION("Arithmetic operators")
    {
        {
            const auto x = Kbza::Address<1>::create_aligned(32);

            REQUIRE((x + 0).value() == 32);
            REQUIRE((x + 1).value() == 33);
            REQUIRE((x + 2).value() == 34);

            REQUIRE(x.value() == 32);

            REQUIRE((x + (-1)).value() == 31);
            REQUIRE((x + (-2)).value() == 30);
            REQUIRE((x + (-3)).value() == 29);

            REQUIRE(x.value() == 32);

            REQUIRE((x - 0).value() == 32);
            REQUIRE((x - 1).value() == 31);
            REQUIRE((x - 2).value() == 30);

            REQUIRE(x.value() == 32);

            REQUIRE((x - (-1)).value() == 33);
            REQUIRE((x - (-2)).value() == 34);
            REQUIRE((x - (-3)).value() == 35);

            REQUIRE(x.value() == 32);
        }

        {
            const auto x = Kbza::Address<2>::create_aligned(32);

            REQUIRE((x + 0).value() == 32);
            REQUIRE((x + 1).value() == 34);
            REQUIRE((x + 2).value() == 36);

            REQUIRE(x.value() == 32);

            REQUIRE((x + (-1)).value() == 30);
            REQUIRE((x + (-2)).value() == 28);
            REQUIRE((x + (-3)).value() == 26);

            REQUIRE(x.value() == 32);

            REQUIRE((x - 0).value() == 32);
            REQUIRE((x - 1).value() == 30);
            REQUIRE((x - 2).value() == 28);

            REQUIRE(x.value() == 32);

            REQUIRE((x - (-1)).value() == 34);
            REQUIRE((x - (-2)).value() == 36);
            REQUIRE((x - (-3)).value() == 38);

            REQUIRE(x.value() == 32);
        }

        {
            const auto x = Kbza::Address<4>::create_aligned(32);

            REQUIRE((x + 0).value() == 32);
            REQUIRE((x + 1).value() == 36);
            REQUIRE((x + 2).value() == 40);

            REQUIRE(x.value() == 32);

            REQUIRE((x + (-1)).value() == 28);
            REQUIRE((x + (-2)).value() == 24);
            REQUIRE((x + (-3)).value() == 20);

            REQUIRE(x.value() == 32);

            REQUIRE((x - 0).value() == 32);
            REQUIRE((x - 1).value() == 28);
            REQUIRE((x - 2).value() == 24);

            REQUIRE(x.value() == 32);

            REQUIRE((x - (-1)).value() == 36);
            REQUIRE((x - (-2)).value() == 40);
            REQUIRE((x - (-3)).value() == 44);

            REQUIRE(x.value() == 32);
        }
    }

    SECTION("Arithmetic assignment operators")
    {
        {
            auto x = Kbza::Address<1>::create_aligned(32);

            x += 0;
            REQUIRE(x.value() == 32);

            x += 1;
            REQUIRE(x.value() == 33);

            x += 2;
            REQUIRE(x.value() == 35);
        }

        {
            auto x = Kbza::Address<1>::create_aligned(32);

            x += -1;
            REQUIRE(x.value() == 31);

            x += -2;
            REQUIRE(x.value() == 29);

            x += -3;
            REQUIRE(x.value() == 26);
        }

        {
            auto x = Kbza::Address<1>::create_aligned(32);

            x -= 0;
            REQUIRE(x.value() == 32);

            x -= 1;
            REQUIRE(x.value() == 31);

            x -= 2;
            REQUIRE(x.value() == 29);
        }

        {
            auto x = Kbza::Address<1>::create_aligned(32);

            x -= -1;
            REQUIRE(x.value() == 33);

            x -= -2;
            REQUIRE(x.value() == 35);

            x -= -3;
            REQUIRE(x.value() == 38);
        }

        {
            auto x = Kbza::Address<2>::create_aligned(32);

            x += 0;
            REQUIRE(x.value() == 32);

            x += 1;
            REQUIRE(x.value() == 34);

            x += 2;
            REQUIRE(x.value() == 38);
        }

        {
            auto x = Kbza::Address<2>::create_aligned(32);

            x += -1;
            REQUIRE(x.value() == 30);

            x += -2;
            REQUIRE(x.value() == 26);

            x += -3;
            REQUIRE(x.value() == 20);
        }

        {
            auto x = Kbza::Address<2>::create_aligned(32);

            x -= 0;
            REQUIRE(x.value() == 32);

            x -= 1;
            REQUIRE(x.value() == 30);

            x -= 2;
            REQUIRE(x.value() == 26);
        }

        {
            auto x = Kbza::Address<2>::create_aligned(32);

            x -= -1;
            REQUIRE(x.value() == 34);

            x -= -2;
            REQUIRE(x.value() == 38);

            x -= -3;
            REQUIRE(x.value() == 44);
        }

        {
            auto x = Kbza::Address<4>::create_aligned(32);

            x += 0;
            REQUIRE(x.value() == 32);

            x += 1;
            REQUIRE(x.value() == 36);

            x += 2;
            REQUIRE(x.value() == 44);
        }

        {
            auto x = Kbza::Address<4>::create_aligned(32);

            x += -1;
            REQUIRE(x.value() == 28);

            x += -2;
            REQUIRE(x.value() == 20);

            x += -3;
            REQUIRE(x.value() == 8);
        }

        {
            auto x = Kbza::Address<4>::create_aligned(32);

            x -= 0;
            REQUIRE(x.value() == 32);

            x -= 1;
            REQUIRE(x.value() == 28);

            x -= 2;
            REQUIRE(x.value() == 20);
        }

        {
            auto x = Kbza::Address<4>::create_aligned(32);

            x -= -1;
            REQUIRE(x.value() == 36);

            x -= -2;
            REQUIRE(x.value() == 44);

            x -= -3;
            REQUIRE(x.value() == 56);
        }
    }
}
