/**
 *  Rom class for the C++ version of Goober  
 * 
 *  @author Brenden Davidson <davidson.brenden15@gmail.com>
 *  @date Oct. 30, 2019
 *  @version 0.1
 */

#include <fstream>
#include <iostream>

#include "Rom.hpp"
#include <RomConstants.hpp>

using namespace goober;

Rom::Rom() {
    title = "UNDEFINED";
    mfgCode = "UNDEFINED";
    cartType = "UNDEFINED";
    licensee = "UNDEFINED";
};

Rom::Rom(const fs::path& romFile) {
    title = "UNDEFINED";
    mfgCode = "UNDEFINED";
    cartType = "UNDEFINED";
    licensee = "UNDEFINED";
    loadRom(romFile);
}

/**
 * Loads the specified ROM into memory.
 * 
 * @param romPath path to the ROM
 */
void Rom::loadRom(const fs::path& romPath) {
    // Starting at the end of the file lets us immediately determine its size.
    std::ifstream romFile(romPath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!romFile.is_open()) {
        std::cerr << "Failed to open ROM file " << romPath.string() << std::endl;
        throw std::runtime_error("Failed to open ROM file.");
    }

    dword romSize = static_cast<dword>(romFile.tellg());
    // Reset our seek to the beginning of the file
    romFile.seekg(0, std::ios::beg);
    // Read the file into a vector for processing
    std::vector<char> romBytes(romSize);
    romFile.read(romBytes.data(), romSize);
    romFile.close();

    // Determine our expected values
    word numBanks = romSize >> static_cast<byte>(14); // Same as dividing by 16,384 but much faster
    char expectedBanksHex = romBytes[0x0148];
    word numExpectedBanks = goober::ROM_BANK_MAP[expectedBanksHex];

    // Check if the expected and actual bank numbers match up
    if (numBanks != numExpectedBanks && numBanks != 2) {
        std::clog << "WARN: Actual ROM size does not match expected size." << std::endl;
        bankCount = numBanks;
    } else {
        bankCount = numExpectedBanks;
    }

    // Split the ROM into banks and convert to byte
    for (word i = 0; i < numBanks; i++) {
        RomBank tempBank;
        for (dword j = 0; j < ROM_BANK_SIZE; j++) {
            dword romBytesLoc = (ROM_BANK_SIZE * i) + j;
            tempBank[j] = static_cast<byte>(romBytes[romBytesLoc]);
        }

        romBanks.push_back(tempBank);
    }

    bankCount = numBanks;
    saveRomInfo();
}

/**
 * Uses the header data in bank00 to populate member variables containing
 * data useful for ROM compatibility.
 */
void Rom::saveRomInfo() {
    // Grab the game title
    char tmpTitle[16];
    for (int i = 0x0134; i < 0x0144; i++) {
        int idx = i - 0x0134;
        tmpTitle[idx] = static_cast<char>(romBanks[0][i]);
    }
    tmpTitle[15] = '\0';
    title = tmpTitle;

    // Get the manufacturing code
    char tmpMfgCode[5];
    for (int i = 0x013F; i <= 0x0142; i++) {
        int idx = i - 0x013F;
        tmpMfgCode[idx] = static_cast<char>(romBanks[0][i]);
    }
    tmpMfgCode[4] = '\0';
    mfgCode = tmpMfgCode;

    // Everything else can be directly accessed.
    cgbOnly         = CGB_FLAG_MAP[romBanks[0][0x0143]];
    sgbSupport      = SGB_FLAG_MAP[romBanks[0][0x0146]];
    japanOnly       = DEST_CODE_MAP[romBanks[0][0x014A]];
    licensee        = determineLicensee(romBanks[0][0x014B]);
    cartType        = CART_TYPE_MAP[romBanks[0][0x0147]];
    ramSize         = RAM_SIZE_MAP[romBanks[0][0x0149]];
    versionNumber   = romBanks[0][0x014C];
}


/**
 * Returns the appropriate licensee based on the value passed in.
 * 
 * @param code hex code from the address 0x014B in ROM
 * @return string containing the licensee name if it was found
 */
string Rom::determineLicensee(const byte& code) {
    string tmpLicensee;

    if (code == 0x33) {
        // Read directly from bytes 0x0144 and 0x0145
        byte asciiCode[] = {
            romBanks[0][0x0144], romBanks[0][0x0145]
        };
        tmpLicensee = reinterpret_cast<const char *>(asciiCode);
    } else {
        tmpLicensee = OLD_LICENSEES_MAP[code];
    }

    return tmpLicensee;
}

/**
 * Returns the byte found at the specified address.
 * 
 * @param address location in ROM to read from
 * @return a single byte containing the read data
 */
byte Rom::read(const mem_loc& address) {
    if ( address <= 0x3FFF) {
        // Read from bank00
        return romBanks[0][address];
    } else {
        // Read from switchable bankNN
        word location = address - 0x4000;
        return romBanks[activeBank][location];
    }
}

/**
 * Sets which memory bank to use in place of bankNN.
 * 
 * @param bankIdx index of the bank to switch bankNN over to
 */
void Rom::setBank(const mem_loc& bankIdx) {
    activeBank = bankIdx;
}

/**
 * Copies the data from inData to loadBank.
 *
 * @param inData
 */
void Rom::loadBank00(const word* inData) {
    for (int i = 0; i < 16384; i++) {
        romBanks[0][i] = inData[i];
    }
}

/**
 * Copies the data from inData to bankNN.
 *
 * @param inData
 */
void Rom::loadBankNN(const word* inData) {
    for (int i = 0; i < 16384; i++) {
        romBanks[activeBank][i] = inData[i];
    }
}
