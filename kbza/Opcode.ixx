module;

#include <cstdint>

export module Kbza:Opcode;

export namespace Kbza
{

    /// @brief
    enum class Opcode : std::uint16_t
    {
        // XXX_R_I8  [ 6 | 0x0000 - 0x5000 ]
        // ------------------------------------
        MOV_R_I8     = 0x0000,
        MOVS_R_I8    = 0x1000,

        // XXX_I12   [ 2 | 0x6000 - 0x7000 ]
        // ------------------------------------
        CALL_I12     = 0x6000,
        JMP_I12      = 0x7000,

        // XXX_R_I4  [ 16 | 0x8000 - 0x8F00 ]
        // ------------------------------------
        LSHL0_R_I4   = 0x8000,
        LSHL1_R_I4   = 0x8100,
        LSHR0_R_I4   = 0x8200,
        LSHR1_R_I4   = 0x8300,

        // XXX_R     [ 32 | 0xA000 - 0xA1F0 ]
        // ------------------------------------
        PUSH_R       = 0xA000,
        POP_R        = 0xA010,
        JMP_R        = 0xA020,
        CALL_R       = 0xA030,
        MOV_R_I16    = 0xA040,
        MOV_R_I32    = 0xA050,
        MOV_R_I64    = 0xA060,
        MOVS_R_I16   = 0xA070,
        MOVS_R_I32   = 0xA080,

        // XXX_R_R   [ 93 | 0xA200 - 0xFE00 ]
        // ------------------------------------
        SWP_R_R      = 0xA200,
        MOV_R_R      = 0xA300,
        MOVS_R_R8    = 0xA400,
        MOVS_R_R16   = 0xA500,
        MOVS_R_R32   = 0xA600,
        MOV_R_M8     = 0xA700,
        MOV_R_M16    = 0xA800,
        MOV_R_M32    = 0xA900,
        MOV_R_M64    = 0xAA00,
        MOVS_R_M8    = 0xAB00,
        MOVS_R_M16   = 0xAC00,
        MOVS_R_M32   = 0xAD00,
        MOV_M8_R     = 0xAE00,
        MOV_M16_R    = 0xAF00,
        MOV_M32_R    = 0xB000,
        MOV_M64_R    = 0xB100,
        AND_R_R      = 0xC000,
        OR_R_R       = 0xC100,
        XOR_R_R      = 0xC200,
        TEST_R_R     = 0xC300,
        ADD_R_R      = 0xD000,
        SUB_R_R      = 0xD100,

        // XXX       [ 256 | 0xFF00 - 0xFFFF ]
        // ------------------------------------
        RET          = 0xFF00,
        STI          = 0xFF01,
        CLI          = 0xFF02,
        CPUID        = 0xFFFE,
        HALT         = 0xFFFF,
    };

}
