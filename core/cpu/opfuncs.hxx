#ifndef GOOBER_OPFUNCS_HXX
#define GOOBER_OPFUNCS_HXX

#include "../mmu/Mmu.hpp"

#include <Definitions.hpp>

using namespace goober;

struct ByteLdArgs {
    byte*   reg;
    word*   pc;
    MMU*    mmu;
};

struct ByteRegLdArgs {
    byte*   reg1;
    byte*   reg2;
};

// Arguments for opfuncs are passed through structs.
typedef void (*opfunc)(void*);

/**
 * NOP does absolutely nothing except take up 4 clock cycles.
*/
void NOP(void* ignore);

/**
 * HALT powers down the CPU until an interrupt occurs.
*/
void HALT(void* ignore);

/**
 * Loads the immediate 8-bit value into the specified register.
*/
void LD_nn_n(ByteLdArgs ldArgs);

/**
 * Loads the value from register 2 into register 1.
*/
void LD_r1_r2(ByteRegLdArgs ldArgs);

enum class OpCode {
    NOP = 0x00,
    HALT = 0x76,
    // 8-bit immediate loads
    LD_b_n = 0x06,
    LD_c_n = 0x0E,
    LD_d_n = 0x16,
    LD_e_n = 0x1E,
    LD_h_n = 0x26,
    LD_l_n = 0x2E,
    // 8-bit register loads
    LD_a_a = 0x7F,
    LD_a_b = 0x78,
    LD_a_c = 0x79,
    LD_a_d = 0x7A,
    LD_a_e = 0x7B,
    LD_a_h = 0x7C,
    LD_a_l = 0x7D,
    LD_b_b = 0x40,
    LD_b_c = 0x41,
    LD_b_d = 0x42,
    LD_b_e = 0x43,
    LD_b_h = 0x44,
    LD_b_l = 0x45,
    LD_c_b = 0x48,
    LD_c_c = 0x49,
    LD_c_d = 0x4A,
    LD_c_e = 0x4B,
    LD_c_h = 0x4C,
    LD_c_l = 0x4D,
    LD_d_b = 0x50,
    LD_d_c = 0x51,
    LD_d_d = 0x52,
    LD_d_e = 0x53,
    LD_d_h = 0x54,
    LD_d_l = 0x55,
    LD_e_b = 0x58,
    LD_e_c = 0x59,
    LD_e_d = 0x5A,
    LD_e_e = 0x5B,
    LD_e_h = 0x5C,
    LD_e_l = 0x5D,
    LD_h_b = 0x60,
    LD_h_c = 0x61,
    LD_h_d = 0x62,
    LD_h_e = 0x63,
    LD_h_h = 0x64,
    LD_h_l = 0x65,
    LD_l_b = 0x68,
    LD_l_c = 0x69,
    LD_l_d = 0x6A,
    LD_l_e = 0x6B,
    LD_l_h = 0x6C,
    LD_l_l = 0x6D,
    // 8-bit register loads using pointers from HL
    LD_a_hlMem = 0x7E,
    LD_b_hlMem = 0x46,
    LD_c_hlMem = 0x4E,
    LD_d_hlMem = 0x56,
    LD_e_hlMem = 0x5E,
    LD_h_hlMem = 0x66,
    LD_l_hlMem = 0x6E,
    // 8-bit load into memory pointed to by HL
    LD_hlMem_b = 0x70,
    LD_hlMem_c = 0x71,
    LD_hlMem_d = 0x72,
    LD_hlMem_e = 0x73,
    LD_hlMem_h = 0x74,
    LD_hlMem_l = 0x75,
    LD_hlMem_n = 0x36,
};

#endif // GOOBER_OPFUNCS_HXX