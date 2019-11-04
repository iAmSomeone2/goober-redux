//
// Created by bdavidson on 10/31/19.
//

#ifndef GOOBER_ROMBANK_HPP
#define GOOBER_ROMBANK_HPP

#include <cstdint>
#include <vector>
#include <array>

#include <RomConstants.hpp>

namespace goober {
    class RomBank {
    private:
        std::array<uint8_t, ROM_BANK_SIZE> data{};
    public:
        /**
         * Creates a RomBank object.
         */
        RomBank();
        /**
         * Creates a RomBank object with initialization data.
         * @param initData uint8_t array of size 16384
         */
        explicit RomBank(const uint8_t *initData);
        /**
         * Creates a RomBank object with initialization data.
         * @param initData char array of size 16384
         */
        explicit RomBank(const char *initData);
        /**
         * Creates a RomBank object with initialization data.
         * @param initData uint8_t vector of size 16384
         */
        explicit RomBank(const std::vector<uint8_t>& initData);
        /**
         * Creates a RomBank object with initialization data.
         * @param initData char vector of size 16384
         */
        explicit RomBank(const std::vector<char>& initData);

        /**
         * Read the value at the specified address.
         *
         * @param address location in the bank to read from
         * @return uint8_t containing the requested data.
         */
        uint8_t read(uint16_t address);

        uint8_t &operator[](uint16_t index);

        /**
         * Loads data into the ROM bank.
         * @param initData uint8_t array of size 16384
         */
        void loadBank(const uint8_t *initData);
        /**
         * Loads data into the ROM bank.
         * @param initData char array of size 16384
         */
        void loadBank(const char *initData);
        /**
         * Loads data into the ROM bank.
         * @param initData uint8_t vector of size 16384
         */
        void loadBank(const std::vector<uint8_t>& initData);
        /**
         * Loads data into the ROM bank.
         * @param initData char vector of size 16384
         */
        void loadBank(const std::vector<char>& initData);
    };
};

#endif //GOOBER_ROMBANK_HPP
