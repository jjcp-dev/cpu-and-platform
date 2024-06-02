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
    registers[15] = Kbza::Address<8>::create_aligned(memory_ctrl.span().size_bytes()).value();
}

void Kbza::Core::push(std::uint64_t value)
{
    auto sp = Kbza::Address<8>::create_aligned(registers[15]) - 1;

    memory_ctrl.write(sp, value);

    registers[15] = sp.value();
}

std::uint64_t Kbza::Core::pop()
{
    const auto sp = Kbza::Address<8>::create_aligned(registers[15]);

    const auto value = memory_ctrl.read<std::uint64_t>(sp);

    registers[15] = (sp + 1).value();

    return value;
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
    case Opcode::CALL_I12:
        push((pc + 1).value());
        // Fallthrough
    case Opcode::JMP_I12:
        pc += ins.signed_imm12();
        break;
    case Opcode::LSHL0_R_I4:
        registers[ins.reg1()] <<= 0x00 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHL1_R_I4:
        registers[ins.reg1()] <<= 0x10 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHL2_R_I4:
        registers[ins.reg1()] <<= 0x20 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHL3_R_I4:
        registers[ins.reg1()] <<= 0x30 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHR0_R_I4:
        registers[ins.reg1()] >>= 0x00 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHR1_R_I4:
        registers[ins.reg1()] >>= 0x10 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHR2_R_I4:
        registers[ins.reg1()] >>= 0x20 + ins.imm4();
        pc += 1;
        break;
    case Opcode::LSHR3_R_I4:
        registers[ins.reg1()] >>= 0x30 + ins.imm4();
        pc += 1;
        break;
    case Opcode::PUSH_R:
        push(registers[ins.reg1()]);
        pc += 1;
        break;
    case Opcode::POP_R:
        registers[ins.reg1()] = pop();
        pc += 1;
        break;
    default:
        std::cout << "EOP: " << (std::uint16_t)ins.opcode() << std::endl;
    }
}
