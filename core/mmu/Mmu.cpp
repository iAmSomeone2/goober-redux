//
// Created by bdavidson on 11/3/19.
//

#include <iostream>
#include <boost/format.hpp>

#include "Mmu.hpp"

using namespace goober;

/**
 * Initializes the MMU with a rom path so that the correct RAM variables can
 * be set immediately.
 * @param romPath path on filesystem to the ROM file.
 */
MMU::MMU(const std::filesystem::path& romPath) {
    rom = new Rom(romPath);
    ram = new Ram(1, rom->getRamSize(), 2);
    isInitialized = true;
}


MMU::MMU() {
    rom = new Rom();
    ram = new Ram();
    isInitialized = false;
}

MMU::~MMU() {
    delete(rom);
    delete(ram);
}

void MMU::init(const std::filesystem::path &romPath) {
    rom->loadRom(romPath);

    // Video RAM and Work RAM will be resizeable when GBC support is implemented.
    ram->setVRamBankCount(1);
    ram->setExRamBankCount(rom->getRamSize());
    ram->setWRamBankCount(1);
    isInitialized = true;
}

/**
 * Retrieves the byte at the specified memory address.
 *
 * Accessing the ROM and accessing RAM are functionally identical.
 * @param address
 * @return
 */
byte MMU::get(const mem_loc& address) {
    if (!isInitialized) {
        throw std::runtime_error("MMU not initialized.");
    }

    byte value = 0;

    if (address < VRAM_START_IDX) {
        value = rom->read(address);
    } else {
        value = ram->get(address);
    }

    return value;
}

/**
 * Sets a byte at the specified address.
 *
 * Setting MBC values will be implemented soon. For now, only RAM access
 * is allowed.
 * @param value byte to write
 * @param address location to write to
 */
void MMU::set(const byte& value, const mem_loc& address) {
    if (!isInitialized) {
        throw std::runtime_error("MMU not initialized.");
    }

    if (address < VRAM_START_IDX) {
        std::clog << boost::format("Attempted to write to ROM at 0x%04x") %address << std::endl;
    } else {
        ram->set(value, address);
    }
}
