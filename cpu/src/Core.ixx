module;

#include <cstdint>
#include <array>
#include <concepts>
#include <span>

export module Cpu:Core;

import :RegisterId;
import :Instruction;
import :Status;

import Platform;

using namespace std;

using Platform::MemoryController;
using Platform::Address;

export namespace Cpu
{

    /// @brief
    class Core
    {
    public:

        class State
        {
        public:

            auto get(RegisterId reg) const
            {
                return registers[reg.number()];
            }

            auto get(RegisterId::ProgramCounterId) const
            {
                return pc;
                // return pc.value();
            }

            auto get(RegisterId::StatusId) const
            {
                return status;
            }
            
            void set(RegisterId reg, std::uint64_t value)
            {
                registers[reg.number()] = value;
            }
            
            // void set(RegisterId::ProgramCounterId, Address<2> addr)
            // {
            //     pc = addr;
            // }

        private:
            array<uint64_t, 16> registers;
            uint64_t            pc;
            Cpu::Status         status;
        };

        explicit Core(MemoryController& ctrl)
            : memory_ctrl{ ctrl }
        {
            reset();
        }

        auto get(RegisterId reg) const
        {
            return registers[reg.number()];
        }

        auto get(RegisterId::ProgramCounterId) const
        {
            return pc.value();
        }
        
        void set(RegisterId reg, std::uint64_t value)
        {
            registers[reg.number()] = value;
        }
        
        void set(RegisterId::ProgramCounterId, Address<2> addr)
        {
            pc = addr;
        }

        void reset();

        void step();

    private:

        std::array<std::uint64_t, 16> registers;
        MemoryController& memory_ctrl;
        Address<2> pc;
        Status status = { 0 };

        void push(std::uint64_t value);
        std::uint64_t pop();
    };
}
