module;

#include <cstdint>

export module Cpu:Opcode;

export namespace Cpu
{

    /// @brief
    enum class Opcode : std::uint16_t
    {
        // XXX_R_I8  [ 6 | 0x0000 - 0x5000 ]
        // -------------------------------------------
        MOV_R_I8     = 0x0000, // 0000'iiii'iiii'rrrr
        MOVS_R_I8    = 0x1000, // 0001'iiii'iiii'rrrr

        // XXX_I12   [ 2 | 0x6000 - 0x7000 ]
        // -------------------------------------------
        CALL_I12     = 0x6000, // 0110'iiii'iiii'iiii
        JMP_I12      = 0x7000, // 0111'iiii'iiii'iiii

        // XXX_R_I4  [ 16 | 0x8000 - 0x8F00 ]
        // -------------------------------------------
        LSHL0_R_I4   = 0x8000, // 1000'0000'iiii'rrrr
        LSHL1_R_I4   = 0x8100, // 1000'0001'iiii'rrrr
        LSHL2_R_I4   = 0x8200, // 1000'0010'iiii'rrrr
        LSHL3_R_I4   = 0x8300, // 1000'0011'iiii'rrrr
        LSHR0_R_I4   = 0x8400, // 1000'0100'iiii'rrrr
        LSHR1_R_I4   = 0x8500, // 1000'0101'iiii'rrrr
        LSHR2_R_I4   = 0x8600, // 1000'0110'iiii'rrrr
        LSHR3_R_I4   = 0x8700, // 1000'0111'iiii'rrrr

        // XXX_R     [ 32 | 0xA000 - 0xA1F0 ]
        // -------------------------------------------
        PUSH_R       = 0xA000, // 1010'0000'0000'rrrr
        POP_R        = 0xA010, // 1010'0000'0001'rrrr
        CALL_R       = 0xA020, // 1010'0000'0010'rrrr
        JMP_R        = 0xA030, // 1010'0000'0011'rrrr
        MOV_R_I16    = 0xA040, // 1010'0000'0100'rrrr
        MOV_R_I32    = 0xA050, // 1010'0000'0101'rrrr
        MOV_R_I64    = 0xA060, // 1010'0000'0110'rrrr
        MOVS_R_I16   = 0xA070, // 1010'0000'0111'rrrr
        MOVS_R_I32   = 0xA080, // 1010'0000'1000'rrrr

        // XXX_R_R   [ 93 | 0xA200 - 0xFE00 ]
        // -------------------------------------------
        SWP_R_R      = 0xA200, // 1010'0010'rrrr'rrrr
        MOV_R_R      = 0xA300, // 1010'0011'rrrr'rrrr
        MOVS_R_R8    = 0xA400, // 1010'0100'rrrr'rrrr
        MOVS_R_R16   = 0xA500, // 1010'0101'rrrr'rrrr
        MOVS_R_R32   = 0xA600, // 1010'0110'rrrr'rrrr
        MOV_R_M8     = 0xA700, // 1010'0111'rrrr'rrrr
        MOV_R_M16    = 0xA800, // 1010'1000'rrrr'rrrr
        MOV_R_M32    = 0xA900, // 1010'1001'rrrr'rrrr
        MOV_R_M64    = 0xAA00, // 1010'1010'rrrr'rrrr
        MOVS_R_M8    = 0xAB00, // 1010'1011'rrrr'rrrr
        MOVS_R_M16   = 0xAC00, // 1010'1100'rrrr'rrrr
        MOVS_R_M32   = 0xAD00, // 1010'1101'rrrr'rrrr
        MOV_M8_R     = 0xAE00, // 1010'1110'rrrr'rrrr
        MOV_M16_R    = 0xAF00, // 1010'1111'rrrr'rrrr
        MOV_M32_R    = 0xB000, // 1011'0000'rrrr'rrrr
        MOV_M64_R    = 0xB100, // 1011'0001'rrrr'rrrr
        AND_R_R      = 0xC000, // 1100'0000'rrrr'rrrr
        OR_R_R       = 0xC100, // 1100'0001'rrrr'rrrr
        XOR_R_R      = 0xC200, // 1100'0010'rrrr'rrrr
        TEST_R_R     = 0xC300, // 1100'0011'rrrr'rrrr
        ADD_R_R      = 0xD000, // 1101'0000'rrrr'rrrr
        SUB_R_R      = 0xD100, // 1101'0001'rrrr'rrrr
        ADDC_R_R     = 0xD200, // 1101'0010'rrrr'rrrr
        SUBC_R_R     = 0xD300, // 1101'0011'rrrr'rrrr

        // XXX       [ 256 | 0xFF00 - 0xFFFF ]
        // -------------------------------------------
        RET          = 0xFF00, // 1111'1111'0000'0000
        STI          = 0xFF01, // 1111'1111'0001'0001
        CLI          = 0xFF02, // 1111'1111'0010'0010
        CALL_I16     = 0xFF03, // 1111'1111'0011'0010
        CALL_I32     = 0xFF04, // 1111'1111'0100'0010
        // CALL_I64  = 0xFF05, // 1111'1111'0101'0010
        JMP_I16      = 0xFF06, // 1111'1111'0110'0010
        JMP_I32      = 0xFF07, // 1111'1111'0111'0010
        // JMP_I64   = 0xFF08, // 1111'1111'1000'0010
        CPUID        = 0xFFFE, // 1111'1111'1111'1110
        HALT         = 0xFFFF, // 1111'1111'1111'1111
    };

}
