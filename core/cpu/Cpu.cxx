#include "Cpu.hxx"

using namespace goober;

// TODO: Initialize Cpu regs to their boot values.
Cpu::Cpu() {
    // Reserve space for the MMU
    this->mmu = new MMU();

    // Load in all operation arguments.
    // 8-bit immediate value loads.
    ByteLdArgs ld_b_n_args = {&this->regBC.hiByte, &this->programCounter, this->mmu};
    ByteLdArgs ld_c_n_args = {&this->regBC.loByte, &this->programCounter, this->mmu};
    ByteLdArgs ld_d_n_args = {&this->regDE.hiByte, &this->programCounter, this->mmu};
    ByteLdArgs ld_e_n_args = {&this->regDE.loByte, &this->programCounter, this->mmu};
    ByteLdArgs ld_h_n_args = {&this->regHL.hiByte, &this->programCounter, this->mmu};
    ByteLdArgs ld_l_n_args = {&this->regHL.loByte, &this->programCounter, this->mmu};
    // 8-bit register loads.
    ByteRegLdArgs ld_a_a_args = {&this->regAF.hiByte, &this->regAF.hiByte};
    ByteRegLdArgs ld_a_b_args = {&this->regAF.hiByte, &this->regBC.hiByte};
    ByteRegLdArgs ld_a_c_args = {&this->regAF.hiByte, &this->regBC.loByte};
    ByteRegLdArgs ld_a_d_args = {&this->regAF.hiByte, &this->regDE.hiByte};
    ByteRegLdArgs ld_a_e_args = {&this->regAF.hiByte, &this->regDE.loByte};
    ByteRegLdArgs ld_a_h_args = {&this->regAF.hiByte, &this->regHL.hiByte};
    ByteRegLdArgs ld_a_l_args = {&this->regAF.hiByte, &this->regHL.loByte};

    // Load in all of the operations.
    this->cpuOps = {
            {OpCode::NOP,   Operation{(opfunc)NOP, nullptr, 4}},
            {OpCode::HALT,  Operation{(opfunc)HALT, nullptr, 4}},
            // 8-bit immediate loads
            {OpCode::LD_b_n, Operation{(opfunc)LD_nn_n, reinterpret_cast<void *>(&ld_b_n_args), 8}},
            {OpCode::LD_c_n, Operation{(opfunc)LD_nn_n, reinterpret_cast<void *>(&ld_c_n_args), 8}},
            {OpCode::LD_d_n, Operation{(opfunc)LD_nn_n, reinterpret_cast<void *>(&ld_d_n_args), 8}},
            {OpCode::LD_e_n, Operation{(opfunc)LD_nn_n, reinterpret_cast<void *>(&ld_e_n_args), 8}},
            {OpCode::LD_h_n, Operation{(opfunc)LD_nn_n, reinterpret_cast<void *>(&ld_h_n_args), 8}},
            {OpCode::LD_l_n, Operation{(opfunc)LD_nn_n, reinterpret_cast<void *>(&ld_l_n_args), 8}},
            // 8-bit register loads
            {OpCode::LD_a_a, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_a_args), 4}},
            {OpCode::LD_a_b, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_b_args), 4}},
            {OpCode::LD_a_c, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_c_args), 4}},
            {OpCode::LD_a_d, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_d_args), 4}},
            {OpCode::LD_a_e, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_e_args), 4}},
            {OpCode::LD_a_h, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_h_args), 4}},
            {OpCode::LD_a_l, Operation{(opfunc)LD_r1_r2, reinterpret_cast<void *>(&ld_a_l_args), 4}},
        };
}

Cpu::~Cpu() {
    delete this->mmu;
}

/**
 * Run includes the main operation loop for the emulated CPU. The ROM file
 * is also loaded into the MMU at this point.
 * 
 * @param romPath filesystem path to GameBoy ROM.
*/
void Cpu::run(const fs::path& romPath) {
    // Load in the rom
    this->mmu->init(romPath);


}

// void Cpu::LDr1_hlMem(const char& reg, const char& not_used) {
//     byte& byteReg = getByteReg(reg);

//     word readLoc = this->regHL.fullWord();
//     word value = this->mmu->get(readLoc);

//     byteReg = value;
// }

// void Cpu::LDhlMem_val(const char& reg, const char& not_used) {
//     // Deal with the situation in which an immediate value is read.
//     bool isImmediate = (reg == 'n');

//     byte value = 0;

//     if (!isImmediate) {
//         byte& byteReg = getByteReg(reg);
//         value = byteReg;
//     } else {
//         word readLoc = this->programCounter;
//         value = this->mmu->get(readLoc);
//     }

//     word writeLoc = this->regHL.fullWord();
//     this->mmu->set(value, writeLoc);
// }