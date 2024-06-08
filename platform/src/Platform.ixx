module;

#include <bit>

export module Platform;

export import :MemoryController;

static_assert(
    std::endian::native == std::endian::little,
    "This library only supports little-endian systems at the moment"
);
