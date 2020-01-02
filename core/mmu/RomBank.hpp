//
// Created by bdavidson on 10/31/19.
//

#ifndef GOOBER_ROMBANK_HPP
#define GOOBER_ROMBANK_HPP

#include <vector>
#include <array>

#include <RomConstants.hpp>
#include <Definitions.hpp>

namespace goober {
    class RomBank {
    private:
        std::array<byte, ROM_BANK_SIZE> data{};
    public:
        /**
         * Creates a RomBank object.
         */
        RomBank();
        /**
         * Creates a RomBank object with initialization data.
         * @param initData byte array of size 16384
         */
        explicit RomBank(const byte *initData);
        /**
         * Creates a RomBank object with initialization data.
         * @param initData char array of size 16384
         */
        explicit RomBank(const char *initData);
        /**
         * Creates a RomBank object with initialization data.
         * @param initData byte vector of size 16384
         */
        explicit RomBank(const std::vector<byte>& initData);
        /**
         * Creates a RomBank object with initialization data.
         * @param initData char vector of size 16384
         */
        explicit RomBank(const std::vector<char>& initData);

        /**
         * Read the value at the specified address.
         *
         * @param address location in the bank to read from
         * @return byte containing the requested data.
         */
        byte read(const mem_loc& address);

        byte &operator[](const mem_loc& index);

        /**
         * Loads data into the ROM bank.
         * @param initData byte array of size 16384
         */
        void loadBank(const byte *initData);
        /**
         * Loads data into the ROM bank.
         * @param initData char array of size 16384
         */
        void loadBank(const char *initData);
        /**
         * Loads data into the ROM bank.
         * @param initData byte vector of size 16384
         */
        void loadBank(const std::vector<byte>& initData);
        /**
         * Loads data into the ROM bank.
         * @param initData char vector of size 16384
         */
        void loadBank(const std::vector<char>& initData);
    };
};

#endif //GOOBER_ROMBANK_HPP
