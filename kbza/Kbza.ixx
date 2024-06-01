module;

#include <bit>

export module Kbza;

export import :Utils;
export import :Address;
export import :Opcode;
export import :RegisterId;
export import :Instruction;
export import :MemoryController;
export import :Status;
export import :Core;

static_assert(
    std::endian::native == std::endian::little,
    "Only supports little-endian systems at the moment"
);
