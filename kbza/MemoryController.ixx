module;

#include <cstdint>
#include <cstring>
#include <algorithm>
#include <concepts>
#include <span>
#include <optional>

export module Kbza:MemoryController;

import :Utils;
import :Address;

export namespace Kbza
{

    /// Interface for the Core to read and write from/to memory or devices
    class MemoryController
    {
    public:
        ///
        template<std::integral T>
        static auto create(std::span<T> buffer) -> std::optional<MemoryController>
        {
            auto address = reinterpret_cast<std::uintptr_t>(buffer.data());

            if (Kbza::is_aligned<8>(address))
            {
                return MemoryController{ buffer };
            }
            else
            {
                return {};
            }
        }

        template <std::integral T>
        T read(Kbza::Address<alignof(T)> address) const
        {
            if (address.value() <= (memory_buffer.size_bytes() - sizeof(T)))
            {
                auto ptr = memory_buffer.data() + address.value();

                return *reinterpret_cast<const T*>(ptr);
            }
            else
            {
                return -1;
            }
        }

        template <std::unsigned_integral T>
        void write(Kbza::Address<alignof(T)> address, T value)
        {
            if (address.value() < memory_buffer.size_bytes())
            {
                auto ptr = reinterpret_cast<T*>(memory_buffer.data() + address.value());

                *ptr = value;
            }
        }

        /// @brief
        /// @return
        std::span<std::uint8_t> span() const
        {
            return memory_buffer;
        }

    private:
        std::span<std::uint8_t> memory_buffer;

        template<std::integral T>
        explicit MemoryController(std::span<T> buffer)
        {
            auto b = reinterpret_cast<std::uint8_t*>(buffer.data());
            auto e = reinterpret_cast<std::uint8_t*>(buffer.data() + buffer.size());

            memory_buffer = { b, e };
        }
    };

}
