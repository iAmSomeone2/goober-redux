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
#include <RomConstants.hxx>


goober::Rom::Rom() {
    title = "UNDEFINED";
    mfgCode = "UNDEFINED";
    cartType = "UNDEFINED";
    licensee = "UNDEFINED";
};

goober::Rom::Rom(const std::filesystem::path& romFile) {
    title = "UNDEFINED";
    mfgCode = "UNDEFINED";
    cartType = "UNDEFINED";
    licensee = "UNDEFINED";
    loadRom(romFile);
}

goober::Rom::~Rom() = default;

/**
 * Loads the specified ROM into memory.
 * 
 * @param romPath path to the ROM
 */
void goober::Rom::loadRom(const std::filesystem::path& romPath) {
    // Starting at the end of the file lets us immediately determine its size.
    std::ifstream romFile(romPath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!romFile.is_open()) {
        std::cerr << "Failed to open ROM file " << romPath.string() << std::endl;
        throw std::runtime_error("Failed to open ROM file.");
    }

    uint32_t romSize = static_cast<uint32_t>(romFile.tellg());
    // Reset our seek to the beginning of the file
    romFile.seekg(0, std::ios::beg);
    // Read the file into a vector for processing
    std::vector<char> romBytes(romSize);
    romFile.read(romBytes.data(), romSize);
    romFile.close();

    // Determine our expected values
    uint16_t numBanks = romSize >> static_cast<uint8_t >(14); // Same as dividing by 16,384 but much faster
    char expectedBanksHex = romBytes[0x0148];
    uint16_t numExpectedBanks = goober::ROM_BANK_MAP[expectedBanksHex];

    // Check if the expected and actual bank numbers match up
    if (numBanks != numExpectedBanks && numBanks != 2) {
        std::clog << "WARN: Actual ROM size does not match expected size." << std::endl;
        bankCount = numBanks;
    } else {
        bankCount = numExpectedBanks;
    }

    // Split the ROM into banks and convert to uint8_t
    for (uint16_t i = 0; i < numBanks; i++) {
        RomBank tempBank;
        for (uint32_t j = 0; j < ROM_BANK_SIZE; j++) {
            uint32_t romBytesLoc = (ROM_BANK_SIZE * i) + j;
            char currentByte = romBytes[romBytesLoc];
            tempBank[j] = static_cast<uint8_t>(currentByte);
        }

        romBanks.push_back(tempBank);
    }

    bankCount = numBanks;
    bank00 = romBanks[0];
    bankNN = romBanks[1];
    saveRomInfo();
}

/**
 * Uses the header data in bank00 to populate member variables containing
 * data useful for ROM compatibility.
 */
void goober::Rom::saveRomInfo() {
    // Grab the game title
    //std::vector<uint8_t>::const_iterator first = bank00->begin() + 0x0134;
    //td::vector<uint8_t>::const_iterator last = bank00->begin() + 0x0143;
    //std::vector<uint8_t> titleBytes(first, last);
    char tmpTitle[16];
    for (int i = 0x0134; i < 0x0144; i++) {
        int idx = i - 0x0134;
        tmpTitle[idx] = static_cast<char>(bank00[i]);
    }
    tmpTitle[15] = '\0';
    title = tmpTitle;
    // Do the same for the manufacturing code
    //first = bank00->begin() + 0x013F;
    //last = bank00->begin() + 0x0142;
    char tmpMfgCode[5];
    for (int i = 0x013F; i <= 0x0142; i++) {
        int idx = i - 0x013F;
        tmpMfgCode[idx] = static_cast<char>(bank00[i]);
    }
    tmpMfgCode[4] = '\0';
    mfgCode = tmpMfgCode;

    // Everything else can be directly accessed.
    cgbOnly = goober::CGB_FLAG_MAP[bank00[0x0143]];
    sgbSupport = goober::SGB_FLAG_MAP[bank00[0x0146]];
    japanOnly = goober::DEST_CODE_MAP[bank00[0x014A]];
    licensee = determineLicensee(bank00[0x014B]);
    cartType = goober::CART_TYPE_MAP[bank00[0x0147]];
    ramSize = goober::RAM_SIZE_MAP[bank00[0x0149]];
    versionNumber = bank00[0x014C];
}


/**
 * Returns the appropriate licensee based on the value passed in.
 * 
 * @param code hex code from the address 0x014B in ROM
 * @return string containing the licensee name if it was found
 */
std::string goober::Rom::determineLicensee(uint8_t code) {
    std::string tmpLicensee;

    if (code == 0x33) {
        // Read directly from bytes 0x0144 and 0x0145
        uint8_t asciiCode[] = {
            bank00[0x0144], bank00[0x0145]
        };
        tmpLicensee = reinterpret_cast<const char *>(asciiCode);
    } else {
        tmpLicensee = goober::OLD_LICENSEES_MAP[code];
    }

    return tmpLicensee;
}

/**
 * Returns the byte found at the specified address.
 * 
 * @param address location in ROM to read from
 * @return a single byte containing the read data
 */
uint8_t goober::Rom::read(uint16_t address) {
    if ( address <= 0x3FFF) {
        // Read from bank00
        return bank00[address];
    } else {
        // Read from switchable bankNN
        uint16_t location = address - 0x4000;
        return bankNN[location];
    }
}

/**
 * Sets which memory bank to use in place of bankNN.
 * 
 * @param bankIdx index of the bank to switch bankNN over to
 */
void goober::Rom::setBank(uint16_t bankIdx) {
    if (bankIdx >= 1 && bankIdx < bankCount) {
        bankNN = romBanks[bankIdx];
    }
}

/**
 * Copies the data from inData to loadBank.
 *
 * @param inData
 */
void goober::Rom::loadBank00(const uint8_t* inData) {
    for (int i = 0; i < 16384; i++) {
        bank00[i] = inData[i];
    }
}

/**
 * Copies the data from inData to bankNN.
 *
 * @param inData
 */
void goober::Rom::loadBankNN(const uint8_t* inData) {
    for (int i = 0; i < 16384; i++) {
        bankNN[i] = inData[i];
    }
}

// Getters
std::string goober::Rom::getTitle() {
    return title;
}

uint8_t goober::Rom::getRamSize() {
    return ramSize;
}

std::string goober::Rom::getCartType() {
    return cartType;
}

std::string goober::Rom::getMfgCode() {
    return mfgCode;
}

std::string goober::Rom::getLicensee() {
    return licensee;
}

uint8_t goober::Rom::getVersionNumber() {
    return versionNumber;
}

bool goober::Rom::getCgbFlag() {
    return cgbOnly;
}

bool goober::Rom::getSgbFlag() {
    return sgbSupport;
}

bool goober::Rom::getJapanFlag() {
    return japanOnly;
}
