#ifndef CORE_HXX
#define CORE_HXX

#include <filesystem>

namespace goober {
    class Rom {
    public:
        /**
         * Constructs a Rom object without reading in a ROM file.
         */
        Rom();

        /**
         * Constructs a Rom object and loads in a ROM file.
         * 
         * @param romFile path to the ROM file to open
         */
        explicit Rom(const std::filesystem::path& romFile);

        /**
         * Loads the specified ROM into memory.
         * 
         * @param romPath path to the ROM
         */
        void loadRom(const std::filesystem::path& romPath);

        /**
         * Returns the byte found at the specified address.
         * 
         * @param address location in ROM to read from
         * @return a single byte containing the read data
         */
        uint8_t read(uint16_t address);

        uint8_t getRamSize();
        std::string getTitle();
        std::string getMfgCode();
        std::string getCartType();
        std::string getLicensee();
        uint8_t getVersionNumber();

        bool getCgbFlag();
        bool getSgbFlag();
        bool getJapanFlag();
    };
}

#endif