//
// Created by bdavidson on 11/1/19.
//

#ifndef GOOBER_RAM_HPP
#define GOOBER_RAM_HPP

#include <vector>

#include "RamBank.hpp"

namespace goober {
    static const uint16_t VRAM_START_IDX = 0x8000;
    static const uint16_t EXRAM_START_IDX = 0xA000;
    static const uint16_t WRAM_START_IDX = 0xC000;
    static const uint16_t MIRROR_START_IDX = 0xE000;
    static const uint16_t ATTRIB_TABLE_START_IDX = 0xFE00;
    static const uint16_t ODDBALL_START_IDX = 0xFEA0;
    static const uint16_t IO_REG_START_IDX = 0xFF00;
    static const uint16_t HRAM_START_IDX = 0xFF80;

    class Ram {
    private:
        /*
            These banks are all separate in the event that special consideration needs
            to be taken with them. 
        */

        std::vector<RamBank> videoRamBanks; // 8192 bytes (each)
        std::vector<RamBank> externRamBanks;// 8192 bytes (each)
        std::vector<RamBank> workRamBanks;  // 4096 bytes (each)
        RamBank spriteAttribTable;          // 383 bytes
        RamBank oddball;                    // 95 bytes
        RamBank ioRegisters;                // 127 bytes
        RamBank highRam;                    // 126 bytes
        uint8_t ieRegister;

        uint8_t activeVideoRamBank;
        uint8_t activeWorkRamBank;
        uint8_t activeExternRamBank;

    public:
        /**
        * Constructs the Ram object. 
        */
        Ram();

        Ram(uint16_t vRamBankCount, uint16_t exRamBankCount, uint16_t workRamBankCount);

        /**
         * Non-destructively resizes the Video RAM Bank vector to hold more banks.
         * @param count new number of banks
         */
        void setVRamBankCount(uint8_t count);

        /**
         * Non-destructively resizes the External RAM Bank vector to hold more banks.
         * @param count new number of banks
         */
        void setExRamBankCount(uint16_t count);

        /**
         * Non-destructively resizes the Work RAM Bank vector to hold more banks.
         * @param count new number of banks
         */
        void setWRamBankCount(uint16_t count);

        /**
         * Retrieves a byte from the specified address.
         * 
         * @param address location to read the byte from
         * @return byte from the location specified
         */
        uint8_t get(const uint16_t& address);

        /**
         * Sets a byte at the specified address.
         * 
         * @param value byte to write to memory
         * @param address location to write to in memory
         */
        void set(uint8_t value, uint16_t address);
    };
};

#endif //GOOBER_RAM_HPP
