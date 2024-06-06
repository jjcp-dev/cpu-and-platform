module;

#include <bit>

export module Cpu;

export import :Opcode;
export import :RegisterId;
export import :Instruction;
export import :Status;
export import :Core;

static_assert(
    std::endian::native == std::endian::little,
    "This library only supports little-endian systems at the moment"
);
