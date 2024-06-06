module;

#include <cstdint>
#include <iostream>

export module Cpu:Core_k;

import Platform;

import :Core;
import :Instruction;
import :Opcode;

using namespace Cpu;
using Platform::Address;

void Core::reset()
{
    for (auto& r : registers)
    {
        r = 0;
    }

    registers[15] = Address<8>::create_aligned(memory_ctrl.span().size_bytes()).value();
    pc            = Address<2>();
    status        = { 0 };
}

void Core::push(std::uint64_t value)
{
    auto sp = Address<8>::create_aligned(registers[15]) - 1;

    memory_ctrl.write(sp, value);

    registers[15] = sp.value();
}

std::uint64_t Core::pop()
{
    const auto sp = Address<8>::create_aligned(registers[15]);

    const auto value = memory_ctrl.read<std::uint64_t>(sp);

    registers[15] = (sp + 1).value();

    return value;
}

void Core::step()
{
    auto ins = Cpu::Instruction{ memory_ctrl.read<std::uint16_t>(pc) };

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
    case Opcode::CALL_R:
        push((pc + 1).value());
        // Fallthrough
    case Opcode::JMP_R:
        pc = Address<2>::create_aligned(registers[ins.reg1()]);
        break;
    case Opcode::MOV_R_I16:
        registers[ins.reg1()] = memory_ctrl.read<std::uint16_t>(pc + 1);
        pc += 2;
        break;
    case Opcode::MOV_R_I32: {
        auto ptr = Address<4>::create_aligned(pc.value()) + 1;
        registers[ins.reg1()] = memory_ctrl.read<std::uint32_t>(ptr);
        pc = (ptr + 1);
        break;
    }
    default:
        std::cout << "EOP: " << (std::uint16_t)ins.opcode() << std::endl;
    }
}
