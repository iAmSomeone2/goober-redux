#ifndef GOOBER_RAM_BANK_HPP
#define GOOBER_RAM_BANK_HPP

#include <vector>
#include <Definitions.hpp>

namespace goober {
    class RamBank {
    private:
        std::vector<byte> data;
    public:
        /**
         * Default constructor for a RAM bank. It defaults to 4KB.
         */
        RamBank();

        /**
         *  Creates a RAM bank of the specified size. 
         */
        explicit RamBank(const int& bankSize);

        /**
         * Sets the size of the data vector.
         *
         * @param bankSize number of bytes to resize to
         */
        void setSize(const int& bankSize);

        /**
         * Provides access to the underlying data vector.
         * 
         * @param index location in array to access
         */
        byte &operator[](const mem_loc& index);

        byte get(const mem_loc& index);

        void set(const byte& value, const mem_loc& index);
    };
};

#endif 