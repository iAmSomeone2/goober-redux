//
// Created by bdavidson on 11/1/19.
//

#ifndef GOOBER_RAM_HPP
#define GOOBER_RAM_HPP

#include <vector>

#include "RamBank.hpp"
#include <Definitions.hpp>

namespace goober {
    static const word VRAM_START_IDX = 0x8000;
    static const word EXRAM_START_IDX = 0xA000;
    static const word WRAM_START_IDX = 0xC000;
    static const word MIRROR_START_IDX = 0xE000;
    static const word ATTRIB_TABLE_START_IDX = 0xFE00;
    static const word ODDBALL_START_IDX = 0xFEA0;
    static const word IO_REG_START_IDX = 0xFF00;
    static const word HRAM_START_IDX = 0xFF80;

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
        byte ieRegister;

        byte activeVideoRamBank;
        byte activeWorkRamBank;
        byte activeExternRamBank;

    public:
        /**
        * Constructs the Ram object. 
        */
        Ram();

        Ram(const word& vRamBankCount, const word& exRamBankCount, const word& workRamBankCount);

        /**
         * Non-destructively resizes the Video RAM Bank vector to hold more banks.
         * @param count new number of banks
         */
        void setVRamBankCount(const byte& count);

        /**
         * Non-destructively resizes the External RAM Bank vector to hold more banks.
         * @param count new number of banks
         */
        void setExRamBankCount(const word& count);

        /**
         * Non-destructively resizes the Work RAM Bank vector to hold more banks.
         * @param count new number of banks
         */
        void setWRamBankCount(const word& count);

        /**
         * Retrieves a byte from the specified address.
         * 
         * @param address location to read the byte from
         * @return byte from the location specified
         */
        byte get(const mem_loc& address);

        /**
         * Sets a byte at the specified address.
         * 
         * @param value byte to write to memory
         * @param address location to write to in memory
         */
        void set(const byte& value, const mem_loc& address);
    };
};

#endif //GOOBER_RAM_HPP
