//
// Created by bdavidson on 11/1/19.
//

#include <iostream>
#include "Ram.hpp"

goober::Ram::Ram() {
    videoRamBanks.resize(1);
    externRamBanks.resize(1);
    workRamBanks.resize(2);

    // Set proper sizes of the banks
    for (auto& bank : videoRamBanks) {
        bank.setSize(8192);
    }
    for (auto& bank : workRamBanks) {
        bank.setSize(4096);
    }
    for (auto& bank : externRamBanks) {
        bank.setSize(8192);
    }
    spriteAttribTable.setSize(383);
    oddball.setSize(95);
    ioRegisters.setSize(127);
    highRam.setSize(126);

    ieRegister = 0x00;
    activeWorkRamBank = 0b01;
    activeVideoRamBank = 0b00;
    activeExternRamBank = 0b00;
}

goober::Ram::Ram(uint16_t vRamBankCount, uint16_t exRamBankCount, uint16_t workRamBankCount) {
    videoRamBanks.resize(vRamBankCount);
    externRamBanks.resize(exRamBankCount);
    workRamBanks.resize(workRamBankCount);

    // Set proper sizes of the banks
    for (auto& bank : videoRamBanks) {
        bank.setSize(8192);
    }
    for (auto& bank : workRamBanks) {
        bank.setSize(4096);
    }
    for (auto& bank : externRamBanks) {
        bank.setSize(8192);
    }
    spriteAttribTable.setSize(383);
    oddball.setSize(95);
    ioRegisters.setSize(127);
    highRam.setSize(126);

    ieRegister = 0x00;
    activeWorkRamBank = 0b01;
    activeVideoRamBank = 0b00;
    activeExternRamBank = 0b00;
}

uint8_t goober::Ram::get(const uint16_t& address) {
    if (address >= VRAM_START_IDX && address < EXRAM_START_IDX) {
        // Video RAM section
        uint16_t location = address - VRAM_START_IDX;
        auto& vBank = videoRamBanks[activeVideoRamBank];
        return vBank[location];
    } else if (address >= EXRAM_START_IDX && address < WRAM_START_IDX) {
        // External RAM section
        uint16_t location = address - EXRAM_START_IDX;
        auto& exBank = externRamBanks[activeExternRamBank];
        return exBank[location];
    } else if (address >= WRAM_START_IDX && address < MIRROR_START_IDX) {
        // Work RAM section
        uint16_t location = address - WRAM_START_IDX;

        RamBank *workBank;
        if (address < 0xD000) {
            workBank = &workRamBanks[0];
        } else {
            workBank = &workRamBanks[activeWorkRamBank];
            location = address - 0xD000;
        }

        return workBank->get(location);
    } else if (address >= MIRROR_START_IDX && address < ATTRIB_TABLE_START_IDX) {
        // Mirror section
        return this->get(address - 0x2000);
    } else if (address >= ATTRIB_TABLE_START_IDX && address < ODDBALL_START_IDX) {
        // Sprite attribute table section
        uint16_t location = address - ATTRIB_TABLE_START_IDX;
        return spriteAttribTable[location];
    } else if (address >= ODDBALL_START_IDX && address < IO_REG_START_IDX) {
        // Oddball section
        uint16_t location = address - ODDBALL_START_IDX;
        return oddball[location];
    } else if (address >= IO_REG_START_IDX && address < HRAM_START_IDX) {
        // I/O register section
        uint16_t location = address - IO_REG_START_IDX;
        return highRam[location];
    } else if (address >= HRAM_START_IDX && address < 0xFFFF) {
        // High RAM section
        uint16_t location = address - HRAM_START_IDX;
        return  highRam[location];
    } else if (address == 0xFFFF) {
        return ieRegister;
    } else {
        std::cerr << "Tried to read from invalid address." << std::endl;
        return 0;
    }
}

void goober::Ram::set(uint8_t value, uint16_t address) {
    if (address >= VRAM_START_IDX && address < EXRAM_START_IDX) {
        // Video RAM section
        uint16_t location = address - VRAM_START_IDX;
        auto& vBank = videoRamBanks[activeVideoRamBank];
        vBank[location] = value;
    } else if (address >= EXRAM_START_IDX && address < WRAM_START_IDX) {
        // External RAM section
        uint16_t location = address - EXRAM_START_IDX;
        auto& exBank = externRamBanks[activeExternRamBank];
        exBank[location] = value;
    } else if (address >= WRAM_START_IDX && address < MIRROR_START_IDX) {
        // Work RAM section
        uint16_t location = address - WRAM_START_IDX;

        RamBank *workBank;
        if (address < 0xD000) {
            workBank = &workRamBanks[0];
        } else {
            workBank = &workRamBanks[activeWorkRamBank];
            location = address - 0xD000;
        }

        workBank->set(value, location);
    } else if (address >= MIRROR_START_IDX && address < ATTRIB_TABLE_START_IDX) {
        // Mirror section
        this->set(value, address - 0x2000);
    } else if (address >= ATTRIB_TABLE_START_IDX && address < ODDBALL_START_IDX) {
        // Sprite attribute table section
        uint16_t location = address - ATTRIB_TABLE_START_IDX;
        spriteAttribTable[location] = value;
    } else if (address >= ODDBALL_START_IDX && address < IO_REG_START_IDX) {
        // Oddball section
        uint16_t location = address - ODDBALL_START_IDX;
        oddball[location] = value;
    } else if (address >= IO_REG_START_IDX && address < HRAM_START_IDX) {
        // I/O register section
        uint16_t location = address - IO_REG_START_IDX;
        highRam[location] = value;
    } else if (address >= HRAM_START_IDX && address < 0xFFFF) {
        // High RAM section
        uint16_t location = address - HRAM_START_IDX;
        highRam[location] = value;
    } else if (address == 0xFFFF) {
        ieRegister = value;
    } else {
        std::cerr << "Tried to set an invalid address." << std::endl;
    }
}

/**
 * Non-destructively resizes the Video RAM Bank vector to hold more banks.
 * @param count new number of banks
 */
void goober::Ram::setVRamBankCount(uint8_t count) {
    videoRamBanks.resize(count);
}

/**
 * Non-destructively resizes the External RAM Bank vector to hold more banks.
 * @param count new number of banks
 */
void goober::Ram::setExRamBankCount(uint16_t count) {
    externRamBanks.resize(count);
}

/**
 * Non-destructively resizes the Work RAM Bank vector to hold more banks.
 * @param count new number of banks
 */
void goober::Ram::setWRamBankCount(uint16_t count) {
    workRamBanks.resize(count);
}
