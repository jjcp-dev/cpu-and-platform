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

        auto get(Kbza::RegisterId reg) const
        {
            return registers[reg.number()];
        }

        auto get(Kbza::RegisterId::ProgramCounterId) const
        {
            return pc.value();
        }
        
        void set(Kbza::RegisterId reg, std::uint64_t value)
        {
            registers[reg.number()] = value;
        }
        
        void set(Kbza::RegisterId::ProgramCounterId, Kbza::Address<2> addr)
        {
            pc = addr;
        }

    private:
        Kbza::MemoryController& memory_ctrl;

        std::array<std::uint64_t, 16> registers;
        Kbza::Address<2> pc;
        Kbza::Status status = { 0 };

        void push(std::uint64_t value);
        std::uint64_t pop();
    };

}
