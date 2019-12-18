//
// Created by bdavidson on 11/1/19.
//

#include <iostream>
#include "Ram.hpp"

using namespace goober;

Ram::Ram() {
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
    spriteAttribTable.setSize(160);
    oddball.setSize(96);
    ioRegisters.setSize(128);
    highRam.setSize(128);

    ieRegister = 0x00;
    activeWorkRamBank = 0b01;
    activeVideoRamBank = 0b00;
    activeExternRamBank = 0b00;
}

Ram::Ram(word vRamBankCount, word exRamBankCount, word workRamBankCount) {
    if (vRamBankCount >= 1) {
        videoRamBanks.resize(vRamBankCount);
    } else {
        videoRamBanks.resize(1);
    }
    if (exRamBankCount >= 1) {
        externRamBanks.resize(exRamBankCount);
    } else {
        externRamBanks.resize(1);
    }
    if (workRamBankCount >= 2) {
        workRamBanks.resize(workRamBankCount);
    } else {
        workRamBanks.resize(2);
    }

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
    spriteAttribTable.setSize(160);
    oddball.setSize(96);
    ioRegisters.setSize(128);
    highRam.setSize(128);

    ieRegister = 0x00;
    activeWorkRamBank = 0b01;
    activeVideoRamBank = 0b00;
    activeExternRamBank = 0b00;
}

byte Ram::get(const word& address) {
    if (address >= VRAM_START_IDX && address < EXRAM_START_IDX) {
        // Video RAM section
        word location = address - VRAM_START_IDX;
        auto& vBank = videoRamBanks[activeVideoRamBank];
        return vBank[location];
    } else if (address >= EXRAM_START_IDX && address < WRAM_START_IDX) {
        // External RAM section
        word location = address - EXRAM_START_IDX;
        auto& exBank = externRamBanks[activeExternRamBank];
        return exBank[location];
    } else if (address >= WRAM_START_IDX && address < MIRROR_START_IDX) {
        // Work RAM section
        word location = address - WRAM_START_IDX;

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
        word location = address - ATTRIB_TABLE_START_IDX;
        return spriteAttribTable[location];
    } else if (address >= ODDBALL_START_IDX && address < IO_REG_START_IDX) { // We keep having problems accessing 0xFFEF
        // Oddball section
        word location = address - ODDBALL_START_IDX;
        return oddball[location];
    } else if (address >= IO_REG_START_IDX && address < HRAM_START_IDX) {
        // I/O register section
        word location = address - IO_REG_START_IDX;
        return highRam[location];
    } else if (address >= HRAM_START_IDX && address < 0xFFFF) {
        // High RAM section
        word location = address - HRAM_START_IDX;
        return  highRam[location];
    } else if (address == 0xFFFF) {
        return ieRegister;
    } else {
        std::cerr << "Tried to read from invalid address." << std::endl;
        return 0;
    }
}

void Ram::set(byte value, word address) {
    if (address >= VRAM_START_IDX && address < EXRAM_START_IDX) {
        // Video RAM section
        word location = address - VRAM_START_IDX;
        auto& vBank = videoRamBanks[activeVideoRamBank];
        vBank[location] = value;
    } else if (address >= EXRAM_START_IDX && address < WRAM_START_IDX) {
        // External RAM section
        word location = address - EXRAM_START_IDX;
        auto& exBank = externRamBanks[activeExternRamBank];
        exBank[location] = value;
    } else if (address >= WRAM_START_IDX && address < MIRROR_START_IDX) {
        // Work RAM section
        word location = address - WRAM_START_IDX;

        RamBank *workBank;
        if (location < 0x1000) {
            workBank = &workRamBanks[0];
        } else {
            workBank = &workRamBanks[activeWorkRamBank];
            location = location - 0x1000;
        }

        workBank->set(value, location);
    } else if (address >= MIRROR_START_IDX && address < ATTRIB_TABLE_START_IDX) {
        // Mirror section
        this->set(value, address - 0x2000);
    } else if (address >= ATTRIB_TABLE_START_IDX && address < ODDBALL_START_IDX) {
        // Sprite attribute table section
        word location = address - ATTRIB_TABLE_START_IDX;
        spriteAttribTable[location] = value;
    } else if (address >= ODDBALL_START_IDX && address < IO_REG_START_IDX) {
        // Oddball section
//        std::clog << "Tried to write to the Oddball section." << std::endl;
        word location = address - ODDBALL_START_IDX;
        oddball[location] = value;
    } else if (address >= IO_REG_START_IDX && address < HRAM_START_IDX) {
        // I/O register section
        word location = address - IO_REG_START_IDX;
        highRam[location] = value;
    } else if (address >= HRAM_START_IDX && address < 0xFFFF) {
        // High RAM section
        word location = address - HRAM_START_IDX;
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
void Ram::setVRamBankCount(byte count) {
    videoRamBanks.resize(count);
}

/**
 * Non-destructively resizes the External RAM Bank vector to hold more banks.
 * @param count new number of banks
 */
void Ram::setExRamBankCount(word count) {
    externRamBanks.resize(count);
}

/**
 * Non-destructively resizes the Work RAM Bank vector to hold more banks.
 * @param count new number of banks
 */
void Ram::setWRamBankCount(word count) {
    workRamBanks.resize(count);
}
