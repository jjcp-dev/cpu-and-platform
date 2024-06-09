module;

#include <cstdint>
#include <iostream>
#include <utility>

module Cpu:Core;

import Platform;
import Utils;

import :Core;
import :Instruction;
import :Opcode;

using namespace Cpu;

using Utils::Address;

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

void Core::logical_update_status(std::uint64_t value)
{
    status.overflow = 0;
    status.carry = 0;
    status.sign = value & 0x8000'0000'0000'0000 ? 1 : 0;
    status.zero = value == 0 ? 1 : 0;
}

void Core::arithmetic_update_status(std::uint64_t a, std::uint64_t b, std::uint64_t result, bool carry)
{
    auto sign_a = a & 0x8000'0000'0000'0000;
    auto sign_b = b & 0x8000'0000'0000'0000;
    auto sign_r = result & 0x8000'0000'0000'0000;

    status.sign = result ? 1 : 0;
    status.zero = result == 0 ? 1 : 0;
    status.carry = carry;
    status.overflow = (sign_a & sign_b & ~sign_r) | (~sign_a & ~sign_b & sign_r);
}

void Core::step()
{
    auto ins = Cpu::Instruction{ memory_ctrl.read<std::uint16_t>(pc) };

    switch (ins.opcode())
    {
    // XXX_R_I8  [ 6 | 0x0000 - 0x5000 ]
    // -------------------------------------------
    case Opcode::MOV_R_I8:
        registers[ins.reg1()] = ins.imm8();
        pc += 1;

        break;
    case Opcode::MOVS_R_I8:
        registers[ins.reg1()] = ins.signed_imm8();
        pc += 1;

        break;
    // XXX_I12   [ 2 | 0x6000 - 0x7000 ]
    // -------------------------------------------
    case Opcode::CALL_I12:
        push((pc + 1).value());
        // Fallthrough
    case Opcode::JMP_I12:
        pc += ins.signed_imm12();
        break;
    // XXX_R_I4  [ 16 | 0x8000 - 0x8F00 ]
    // -------------------------------------------
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
    // XXX_R     [ 32 | 0xA000 - 0xA1F0 ]
    // -------------------------------------------
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
    case Opcode::MOV_R_I32: 
    {
        auto ptr = Address<4>::create_aligned(pc.value()) + 1;
        registers[ins.reg1()] = memory_ctrl.read<std::uint32_t>(ptr);
        pc = (ptr + 1);
        break;
    }
    case Opcode::MOV_R_I64: 
    {
        auto ptr = Address<4>::create_aligned(pc.value()) + 1;

        std::uint64_t low = memory_ctrl.read<std::uint32_t>(ptr);
        std::uint64_t high = memory_ctrl.read<std::uint32_t>(ptr + 1);

        registers[ins.reg1()] = low | (high << 32);
        pc = (ptr + 2);
        break;
    }
    case Opcode::MOVS_R_I16: 
        registers[ins.reg1()] = memory_ctrl.read<std::int16_t>(pc + 1);
        pc += 2;
        break;
    case Opcode::MOVS_R_I32: 
    {
        auto ptr = Address<4>::create_aligned(pc.value()) + 1;
        registers[ins.reg1()] = memory_ctrl.read<std::int32_t>(ptr);
        pc = (ptr + 1);
        break;
    }
    // XXX_R_R   [ 93 | 0xA200 - 0xFE00 ]
    // -------------------------------------------
    case Opcode::SWP_R_R: 
        std::swap(registers[ins.reg1()], registers[ins.reg2()]);
        pc += 1;
        break;
    case Opcode::MOV_R_R: 
        registers[ins.reg1()] = registers[ins.reg2()];
        pc += 1;
        break;
    case Opcode::MOVS_R_R8: 
        registers[ins.reg1()] = static_cast<std::int8_t>(registers[ins.reg2()]);
        pc += 1;
        break;
    case Opcode::MOVS_R_R16: 
        registers[ins.reg1()] = static_cast<std::int16_t>(registers[ins.reg2()]);
        pc += 1;
        break;
    case Opcode::MOVS_R_R32: 
        registers[ins.reg1()] = static_cast<std::int32_t>(registers[ins.reg2()]);
        pc += 1;
        break;
    case Opcode::MOV_R_M8: 
    {
        auto ptr = Address<1>::create_aligned(registers[ins.reg2()]);
        registers[ins.reg1()] = memory_ctrl.read<std::uint8_t>(ptr);
        pc += 1;
        break;
    }
    case Opcode::MOV_R_M16: 
    {
        auto ptr = Address<2>::create(registers[ins.reg2()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            registers[ins.reg1()] = memory_ctrl.read<std::uint16_t>(ptr.value());
            pc += 1;
        }
        break;
    }
    case Opcode::MOV_R_M32: 
    {
        auto ptr = Address<4>::create(registers[ins.reg2()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            registers[ins.reg1()] = memory_ctrl.read<std::uint32_t>(ptr.value());
            pc += 1;
        }
        break;
    }
    case Opcode::MOV_R_M64: 
    {
        auto ptr = Address<8>::create(registers[ins.reg2()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            registers[ins.reg1()] = memory_ctrl.read<std::uint64_t>(ptr.value());
            pc += 1;
        }
        break;
    }
    case Opcode::MOVS_R_M8: 
    {
        auto ptr = Address<1>::create_aligned(registers[ins.reg2()]);
        registers[ins.reg1()] = memory_ctrl.read<std::int8_t>(ptr);
        pc += 1;
        break;
    }
    case Opcode::MOVS_R_M16: 
    {
        auto ptr = Address<2>::create(registers[ins.reg2()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            registers[ins.reg1()] = memory_ctrl.read<std::int16_t>(ptr.value());
            pc += 1;
        }
        break;
    }
    case Opcode::MOVS_R_M32: 
    {
        auto ptr = Address<4>::create(registers[ins.reg2()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            registers[ins.reg1()] = memory_ctrl.read<std::int32_t>(ptr.value());
            pc += 1;
        }
        break;
    }
    case Opcode::MOV_M8_R: 
    {
        auto ptr = Address<1>::create_aligned(registers[ins.reg1()]);
        memory_ctrl.write<std::uint8_t>(ptr, registers[ins.reg2()]);
        pc += 1;
        break;
    }
    case Opcode::MOV_M16_R: 
    {
        auto ptr = Address<2>::create(registers[ins.reg1()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            memory_ctrl.write<std::uint16_t>(ptr.value(), registers[ins.reg2()]);
            pc += 1;
        }
        break;
    }
    case Opcode::MOV_M32_R: 
    {
        auto ptr = Address<4>::create(registers[ins.reg1()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            memory_ctrl.write<std::uint32_t>(ptr.value(), registers[ins.reg2()]);
            pc += 1;
        }
        break;
    }
    case Opcode::MOV_M64_R: 
    {
        auto ptr = Address<8>::create(registers[ins.reg1()]);
        if (not ptr.has_value())
        {
            // INTERRUPT
            break;
        }
        else
        {
            memory_ctrl.write<std::uint64_t>(ptr.value(), registers[ins.reg2()]);
            pc += 1;
        }
        break;
    }
    case Opcode::AND_R_R: 
        registers[ins.reg1()] &= registers[ins.reg2()];
        logical_update_status(registers[ins.reg1()]);
        pc += 1;
        break;
    case Opcode::OR_R_R: 
        registers[ins.reg1()] |= registers[ins.reg2()];
        logical_update_status(registers[ins.reg1()]);
        pc += 1;
        break;
    case Opcode::XOR_R_R: 
        registers[ins.reg1()] ^= registers[ins.reg2()];
        logical_update_status(registers[ins.reg1()]);
        pc += 1;
        break;
    case Opcode::TEST_R_R: 
        logical_update_status(registers[ins.reg1()] & registers[ins.reg2()]);
        pc += 1;
        break;
    case Opcode::ADD_R_R: 
    {
        auto a = registers[ins.reg1()];
        auto b = registers[ins.reg2()];
        auto result = a + b;
        arithmetic_update_status(a, b, result, result < a);
        registers[ins.reg1()] = result;
        pc += 1;
        break;
    }
    case Opcode::SUB_R_R: 
    {
        auto a = registers[ins.reg1()];
        auto b = registers[ins.reg2()];
        auto result = a - b;
        arithmetic_update_status(a, b, result, result > a);
        registers[ins.reg1()] = result;
        pc += 1;
        break;
    }
    case Opcode::ADDC_R_R: 
    {
        auto a = registers[ins.reg1()] + status.carry ? 1 : 0;
        auto b = registers[ins.reg2()];
        auto result = a + b;
        arithmetic_update_status(a, b, result, result < a);
        registers[ins.reg1()] = result;
        pc += 1;
        break;
    }
    case Opcode::SUBC_R_R: 
    {
        auto a = registers[ins.reg1()] - status.carry ? 1 : 0;
        auto b = registers[ins.reg2()];
        auto result = a - b;
        arithmetic_update_status(a, b, result, result > a);
        registers[ins.reg1()] = result;
        pc += 1;
        break;
    }
    // XXX       [ 256 | 0xFF00 - 0xFFFF ]
    // -------------------------------------------
    case Opcode::RET: 
        pc = Address<2>::create_aligned(pop());
        break;
    case Opcode::STI: 
        status.interrupts = 1;
        pc += 1;
        break;
    case Opcode::CLI: 
        status.interrupts = 0;
        pc += 1;
        break;
    case Opcode::CALL_I16: 
        push((pc + 2).value());
        pc += memory_ctrl.read<std::int16_t>(pc + 1);
        break;
    // case Opcode::CPUID: 
    //     break;
    // case Opcode::HALT: 
    //     break;
    default:
        std::cout << "EOP: " << (std::uint16_t)ins.opcode() << std::endl;
    }
}
