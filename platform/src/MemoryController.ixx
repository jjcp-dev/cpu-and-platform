module;

#include <cstdint>
#include <concepts>
#include <optional>
#include <span>
#include <cstring>

export module Platform:MemoryController;

import :Address;

import Utils;

export namespace Platform
{

    class MemoryController
    {
    public:

        template<std::integral T>
        static auto create(std::span<T> buffer) -> std::optional<MemoryController>
        {
            auto address = reinterpret_cast<std::uintptr_t>(buffer.data());

            if (Utils::is_aligned<8>(address))
            {
                return MemoryController{ buffer };
            }
            else
            {
                return {};
            }
        }

        template<std::integral T>
        void copy(std::span<T> from, std::uint64_t address)
        {
            if (from.size_bytes() <= memory.size())
            {
                if (memory.size_bytes() - from.size_bytes() >= address)
                {
                    std::memcpy(memory.data() + address, from.data(), from.size_bytes());
                }
            }
        }

        template<std::integral T>
        auto read(Address<alignof(T)> addr) const -> T
        {
            if (memory.size() - sizeof(T) >= addr.value())
            {
                return *reinterpret_cast<T*>(memory.data() + addr.value());
            }

            return 0;
        }

        template<std::integral T>
        void write(Address<alignof(T)> addr, T value)
        {
            if (addr.value() < memory.size())
            {
                if (memory.size() - sizeof(T) >= addr.value())
                {
                    *reinterpret_cast<T*>(memory.data() + addr.value()) = value;
                }
            }
        }

        auto span() const
        {
            return memory;
        }

    private:
        std::span<std::uint8_t> memory;

        template<std::integral T>
        explicit MemoryController(std::span<T> buffer)
        {
            memory = { 
                reinterpret_cast<std::uint8_t*>(buffer.data()),
                reinterpret_cast<std::uint8_t*>(buffer.data() + buffer.size())
            };
        }
    };

}
