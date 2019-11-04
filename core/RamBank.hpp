#ifndef GOOBER_RAM_BANK_HPP
#define GOOBER_RAM_BANK_HPP

#include <vector>
#include <cstdint>

namespace goober {
    class RamBank {
    private:
        std::vector<uint8_t> data;
    public:
        /**
         * Default constructor for a RAM bank. It defaults to 4KB.
         */
        RamBank();

        /**
         *  Creates a RAM bank of the specified size. 
         */
        explicit RamBank(int bankSize);

        /**
         * Sets the size of the data vector.
         *
         * @param bankSize number of bytes to resize to
         */
        void setSize(int bankSize);

        /**
         * Provides access to the underlying data vector.
         * 
         * @param index location in array to access
         */
        uint8_t &operator[](uint16_t index);

        uint8_t get(uint16_t index);

        void set(uint8_t value, uint16_t index);
    };
};

#endif 