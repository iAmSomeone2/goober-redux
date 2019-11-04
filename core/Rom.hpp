#ifndef ROM_HXX
#define ROM_HXX

#include <map>
#include <cstdint>
#include <vector>
#include <string>
#include <filesystem>

#include "RomBank.hpp"


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

    protected:
        // Basic ROM info
        uint16_t bankCount = 0;
        uint8_t ramSize = 0;
        std::string title;
        std::string mfgCode;
        std::string cartType;
        std::string licensee;
        uint8_t versionNumber = 1;

        // Special feature flags
        bool cgbOnly = false;
        bool sgbSupport = false;
        bool japanOnly = false;

        // ROM data
        RomBank bank00;
        RomBank bankNN;
        std::vector<RomBank> romBanks;

    private:
        /**
         * Uses the header data in bank00 to populate member variables containing
         * data useful for ROM compatibility.
         */
        void saveRomInfo();

        /**
         * Returns the appropriate licensee based on the value passed in.
         * 
         * @param code hex code from the address 0x014B in ROM
         * @return string containing the licensee name if it was found
         */
        std::string determineLicensee(uint8_t code);

        /**
         * Sets which memory bank to use in place of bankNN.
         * 
         * @param bankIdx index of the bank to switch bankNN over to
         */
        void setBank(uint16_t bankIdx);

        /**
         * Copies the data from inData to bank00.
         *
         * @param inData
         */
        void loadBank00(const uint8_t* inData);

        /**
         * Copies the data from inData to bankNN.
         *
         * @param inData
         */
        void loadBankNN(const uint8_t* inData);
    };
};
#endif // ROM_HXX