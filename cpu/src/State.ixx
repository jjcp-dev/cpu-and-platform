module;

#include <cstdint>
#include <array>

export module Cpu:State;

import :Status;
import :RegisterId;

using namespace std;

export namespace Cpu
{

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
            // return pc.value();
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

}
