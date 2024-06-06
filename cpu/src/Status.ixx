module;

#include <cstdint>

export module Cpu:Status;

export namespace Cpu
{

    struct Status
    {
        std::uint64_t carry : 1;
        std::uint64_t overflow : 1;
        std::uint64_t zero : 1;
        std::uint64_t sign : 1;
        std::uint64_t interrupts : 1;
    };

}
