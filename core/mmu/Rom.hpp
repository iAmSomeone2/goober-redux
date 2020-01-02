#ifndef ROM_HXX
#define ROM_HXX

#include <map>
#include <cstdint>
#include <vector>
#include <string>
#include <filesystem>

#include "RomBank.hpp"
#include <Definitions.hpp>


using std::string;
namespace fs = std::filesystem;

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
        explicit Rom(const fs::path& romFile);


        /**
         * Loads the specified ROM into memory.
         * 
         * @param romPath path to the ROM
         */
        void loadRom(const fs::path& romPath);

        /**
         * Returns the byte found at the specified address.
         * 
         * @param address location in ROM to read from
         * @return a single byte containing the read data
         */
        byte read(const mem_loc& address);

        // Getters
        /**
         * Returns RAM size
         */
        byte    getRamSize()        { return this->ramSize; };
        /**
         * Returns game title
        */
        string  getTitle()          { return this->title; };
        /**
         * Returns manufacturing code
        */
        string  getMfgCode()        { return this->mfgCode; };
        /**
         * Returns cartridge type
        */
        string  getCartType()       { return this->cartType; };
        /**
         * Returns licensee of original cartridge
        */
        string  getLicensee()       { return this->licensee; };
        /**
         * Returns ROM version number
        */
        byte    getVersionNumber()  { return this->versionNumber; };
        /**
         * Returns "true" if the ROM is only for Game Boy Color
        */
        bool    getCgbFlag()        { return this->cgbOnly; };
        /**
         * Returns "true" if the ROM has enhanced features for the Super Game Boy
        */
        bool    getSgbFlag()        { return this->sgbSupport; };
        /**
         * Returns "true" if the ROM's region is set to Japan. Returns "false" if
         * the region is anywhere else.
        */
        bool    getJapanFlag()      { return this->japanOnly; };

    protected:
        // Basic ROM info
        word bankCount = 0;
        byte ramSize = 0;
        string title;
        string mfgCode;
        string cartType;
        string licensee;
        byte versionNumber = 1;

        // Special feature flags
        bool cgbOnly = false;
        bool sgbSupport = false;
        bool japanOnly = false;

        // ROM data
        std::vector<RomBank> romBanks;
        word activeBank = 1;

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
        string determineLicensee(const byte& code);

        /**
         * Sets which memory bank to use in place of bankNN.
         * 
         * @param bankIdx index of the bank to switch bankNN over to
         */
        void setBank(const mem_loc& bankIdx);

        /**
         * Copies the data from inData to bank00.
         *
         * @param inData
         */
        void loadBank00(const word* inData);

        /**
         * Copies the data from inData to bankNN.
         *
         * @param inData
         */
        void loadBankNN(const word* inData);
    };
};
#endif // ROM_HXX