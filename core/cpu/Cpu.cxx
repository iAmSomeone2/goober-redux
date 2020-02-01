#include <iostream>
#include <boost/format.hpp>

#include "Cpu.hxx"

using namespace goober;

// TODO: Initialize Cpu regs to their boot values.
Cpu::Cpu() {
    // Reserve space for the MMU
    this->mmu = new MMU();

    this->cycleCount = 0;
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

    byte currentByte;
    while (true) {
        // Read current byte and increment program counter.
        currentByte = this->mmu->get(this->programCounter);
        this->programCounter++;

        switch (currentByte) {
            case OpCode::NOP:
               nop();
               this->cycleCount += cpuCycles[OpCode::NOP];
               break;
            case OpCode::HALT:
                halt();
                this->cycleCount += cpuCycles[OpCode::HALT];
                break;
            // 8-bit loads
            // LD_nn_n
            case OpCode::LD_b_n:
                LD_nn_n('b');
                this->cycleCount += cpuCycles[OpCode::LD_b_n];
                break;
            case OpCode::LD_c_n:
                LD_nn_n('c');
                this->cycleCount += cpuCycles[OpCode::LD_c_n];
                break;
            case OpCode::LD_d_n:
                LD_nn_n('d');
                this->cycleCount += cpuCycles[OpCode::LD_d_n];
                break;
            case OpCode::LD_e_n:
                LD_nn_n('e');
                this->cycleCount += cpuCycles[OpCode::LD_e_n];
                break;
            case OpCode::LD_h_n:
                LD_nn_n('h');
                this->cycleCount += cpuCycles[OpCode::LD_h_n];
                break;
            case OpCode::LD_l_n:
                LD_nn_n('l');
                this->cycleCount += cpuCycles[OpCode::LD_l_n];
                break;
            // LD_r1_r2
            case OpCode::LD_a_a:
                LD_r1_r2('a', 'a');
                this->cycleCount += cpuCycles[OpCode::LD_a_a];
                break;
            default:
                std::cerr << boost::format("Unrecognized opcode: 0x%X\n") % currentByte;
        }
    }
}

byte* Cpu::getByteRegister(const char& reg) {
    byte* smallReg;

    switch (reg) {
        case 'a':
            smallReg = &this->regAF.hiByte;
            break;
        case 'f':
            smallReg = &this->regAF.loByte;
            break;
        case 'b':
            smallReg = &this->regBC.hiByte;
            break;
        case 'c':
            smallReg = &this->regBC.loByte;
            break;
        case 'd':
            smallReg = &this->regDE.hiByte;
            break;
        case 'e':
            smallReg = &this->regDE.loByte;
            break;
        case 'h':
            smallReg = &this->regHL.hiByte;
            break;
        case 'l':
            smallReg = &this->regHL.loByte;
            break;
        default:
            return nullptr;
    }

    return smallReg;
}

void Cpu::LD_nn_n(const char& reg) {
    byte* byteReg = getByteRegister(reg);

    byte value = this->mmu->get(this->programCounter);
    this->programCounter++;

    *byteReg = value;
}

void Cpu::LD_r1_r2(const char& reg1, const char& reg2) {
    byte* byteReg1 = getByteRegister(reg1);
    byte* byteReg2 = getByteRegister(reg2);

    *byteReg1 = *byteReg2;
}

void Cpu::LDr1_hlMem(const char& reg) {
    byte* byteReg = getByteRegister(reg);

    word readLoc = this->regHL.fullWord();
    word value = this->mmu->get(readLoc);

    *byteReg = value;
}

void Cpu::LDhlMem_val(const char& reg) {
    // Deal with the situation in which an immediate value is read.
    bool isImmediate = (reg == 'n');

    byte value = 0;

    if (!isImmediate) {
        byte* byteReg = getByteRegister(reg);
        value = *byteReg;
    } else {
        word readLoc = this->programCounter;
        value = this->mmu->get(readLoc);
        this->programCounter++;
    }

    word writeLoc = this->regHL.fullWord();
    this->mmu->set(value, writeLoc);
}