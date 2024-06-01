module;

#include <cstdint>
#include <iostream>

module Kbza:Core;

import :Core;
import :Utils;
import :MemoryController;
import :Instruction;
import :Opcode;

Kbza::Core::Core(Kbza::MemoryController& ctrl)
    : memory_ctrl{ ctrl }
{
    reset();
}

void Kbza::Core::reset()
{
    for (auto& r : registers)
    {
        r = 0;
    }

    pc = Kbza::Address<2>();
    status = { 0 };
    registers[15] = memory_ctrl.span().size_bytes() - 8;
}

void Kbza::Core::step()
{
    auto ins = Kbza::Instruction{ memory_ctrl.read<std::uint16_t>(pc) };

    switch (ins.opcode())
    {
    case Opcode::MOV_R_I8:
        registers[ins.reg1()] = ins.imm8();
        pc += 1;

        break;
    case Opcode::MOVS_R_I8:
        registers[ins.reg1()] = ins.signed_imm8();
        pc += 1;

        break;
    default:
        std::cout << "EOP: " << (std::uint16_t)ins.opcode() << std::endl;
    }
}
