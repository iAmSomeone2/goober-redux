//
// Created by Brenden Davidson on 11/3/19.
//

#ifndef GOOBER_MMU_HPP
#define GOOBER_MMU_HPP

#include <filesystem>

#include "Ram.hpp"
#include "Rom.hpp"

#include <RomConstants.hpp>
#include <Definitions.hpp>

namespace fs = std::filesystem;

namespace goober {
    class MMU {
    private:
        bool isInitialized;
        Ram *ram;
        Rom *rom;

    public:
        /**
         * Initializes the MMU with a rom path so that the correct RAM variables can
         * be set immediately.
         * @param romPath path on filesystem to the ROM file.
         */
        explicit MMU(const fs::path& romPath);

        MMU();

        ~MMU();

        void init(const fs::path& romPath);

        /**
         * Retrieves the byte at the specified memory address.
         *
         * Accessing the ROM and accessing RAM are functionally identical.
         * @param address
         * @return
         */
        byte get(const mem_loc& address);

        /**
         * Sets a byte at the specified address.
         *
         * Setting MBC values will be implemented soon. For now, only RAM access
         * is allowed.
         * @param value byte to write
         * @param address location to write to
         */
        void set(const byte& value, const mem_loc& address);
    };
};

#endif //GOOBER_MMU_HPP
