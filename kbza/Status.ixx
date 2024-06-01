module;

#include <cstdint>

export module Kbza:Status;

export namespace Kbza
{

    struct Status
    {
        std::uint64_t carry : 1;
        std::uint64_t overflow : 1;
        std::uint64_t zero : 1;
        std::uint64_t sign : 1;
    };

}
