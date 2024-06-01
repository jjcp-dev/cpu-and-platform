module;

#include <cstdint>
#include <array>
#include <concepts>

export module Kbza:Core;

import :MemoryController;
import :RegisterId;
import :Instruction;
import :Address;
import :Status;

export namespace Kbza
{

    /// @brief
    class Core
    {
    public:
        explicit Core(Kbza::MemoryController& ctrl);

        void reset();

        void step();

    private:
        Kbza::MemoryController& memory_ctrl;

        std::array<std::uint64_t, 16> registers;
        Kbza::Address<2> pc;
        Kbza::Status status = { 0 };
    };

}
