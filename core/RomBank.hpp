//
// Created by bdavidson on 10/31/19.
//

#ifndef GOOBER_ROMBANK_HPP
#define GOOBER_ROMBANK_HPP

#include <cstdint>
#include <vector>

static const uint16_t BANK_SIZE =  16384;

namespace goober {
    class RomBank {
    private:
        std::vector<uint8_t> data;
    public:
        RomBank();
        explicit RomBank(const uint8_t *initData);
        explicit RomBank(const char *initData);
        explicit RomBank(const std::vector<uint8_t>& initData);
        explicit RomBank(const std::vector<char>& initData);

        /**
         * Read the value at the specified address.
         *
         * @param address location in the bank to read from
         * @return uint8_t containing the requested data.
         */
        uint8_t read(uint16_t address);

        uint8_t &operator[](uint16_t index);

        void loadBank(const uint8_t *initData);
        void loadBank(const char *initData);
        void loadBank(const std::vector<uint8_t>& initData);
        void loadBank(const std::vector<char>& initData);
    };
};

#endif //GOOBER_ROMBANK_HPP
