/**
 *  Rom class for the C++ version of Goober  
 * 
 *  @author Brenden Davidson <davidson.brenden15@gmail.com>
 *  @date Oct. 30, 2019
 */

#include <fstream>
#include <sstream>
#include <iostream>

#include "Rom.hxx"
#include <RomConstants.hxx>

/**
 * Constructs a Rom object without reading in a ROM file.
 */
goober::Rom::Rom() {
    // Resize the bank vectors.
    bank00.resize(16384);
    bankNN.resize(16384);
    //m_title->resize(16);
    //m_mfgCode->resize(3);
}

goober::Rom::Rom(const std::filesystem::path& romFile) {
    bank00.resize(16384);
    bankNN.resize(16384);
    //m_title->resize(16);
    //m_mfgCode->resize(3);

    loadRom(romFile);
}

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
    uint16_t numBanks = romSize >> 14; // Same as dividing by 16,384 but much faster
    char expectedBanksHex = romBytes[0x0148];
    uint16_t numExpectedBanks = goober::ROM_BANK_MAP[expectedBanksHex];

    // Check if the expected and actual bank numbers match up
    if (numBanks != numExpectedBanks && numBanks != 2) {
        std::cerr << "WARN: Actual ROM size does not match expected size." << std::endl;
    }

    romBanks.resize(static_cast<size_t>(numBanks));
    for (auto& bank : romBanks) {
        bank.resize(16384);
    }

    // Split the ROM into banks and convert to uint8_t
    for (uint16_t i = 0; i < numBanks; i++) {
        bank tempBank(16384);
        for (uint32_t j = 0; j < 16384; j++) {
            uint32_t romBytesLoc = (16384 * i) + j;
            char currentByte = romBytes[romBytesLoc];
            tempBank[j] = static_cast<uint8_t>(currentByte);
        }

        if (i == 0) {
            bank00 = tempBank;
        }
        romBanks[i] = tempBank;
    }

    //saveRomInfo();
}

/**
 * Uses the header data in bank00 to populate member variables containing
 * data useful for ROM compatibility.
 */
void goober::Rom::saveRomInfo() {
    // Grab the game title
    std::vector<uint8_t>::const_iterator first = bank00.begin() + 0x0134;
    std::vector<uint8_t>::const_iterator last = bank00.begin() + 0x0143;
    std::vector<uint8_t> titleBytes(first, last);
    // Convert the game title to a string and save it
    m_title.resize(titleBytes.size());
    m_title = titleBytes;
    // Do the same for the manufacturing code
    first = bank00.begin() + 0x013F;
    last = bank00.begin() + 0x0142;
    std::vector<uint8_t> mfgCodeBytes(first, last);
    m_mfgCode.resize(mfgCodeBytes.size());
    m_mfgCode = mfgCodeBytes;

    // Everything else can be directly accessed.
    m_cgbOnly = goober::CGB_FLAG_MAP[bank00[0x0143]];
    m_sgbSupport = goober::SGB_FLAG_MAP[bank00[0x0146]];
    m_cartType = goober::CART_TYPE_MAP[bank00[0x0147]];
    m_romBanks = goober::ROM_BANK_MAP[bank00[0x0148]];
    m_ramSize = goober::RAM_SIZE_MAP[bank00[0x0149]];
    m_japanOnly = goober::DEST_CODE_MAP[bank00[0x014A]];
    m_licensee = getLicensee(bank00[0x014B]);
    m_versionNumber = bank00[0x014C];
}
 
/**
 * Loads in the specified CSV file and returns a map containg the value pairs.
 * 
 * @param filePath path on the filesystem from which to read the file from
 * @return map containing the value pairs
 */
std::map<uint8_t, std::string> goober::Rom::loadCsv(std::filesystem::path filePath) {
    std::ifstream csvFile(filePath, std::ios::in);
    if (!csvFile.is_open()){
        std::cerr << "Failed to open " << filePath.string() << std::endl;
        throw std::runtime_error("Failed to open file.");
    }

    // Count number of lines in the file
    std::string tmp;
    uint32_t numLines = 0;
    while (std::getline(csvFile, tmp)) {
        numLines++;
    }
    csvFile.seekg(0, std::ios::beg);

    // Set up a vector to hold the lines
    std::vector<std::string> lines(numLines);
    uint32_t lineNum = 0;
    while (std::getline(csvFile, tmp)) {
        lines[lineNum] = tmp;
    }

    csvFile.close();

    std::map<uint8_t, std::string> valueMap;

    // Split each line, convert the hex values, and store the results in the return map
    for (const std::string& line : lines) {
        // Find the comma
        auto commaIdx = static_cast<uint32_t>(line.find(',', 0));
        std::string hexCode = line.substr(0, commaIdx);
        std::string strValue = line.substr(commaIdx);

        auto hexVal = static_cast<uint8_t>(std::stoul(hexCode, nullptr, 16));
        valueMap[hexVal] = strValue;
    }

    return valueMap;
}

/**
 * Returns the appropriate licensee based on the value passed in.
 * 
 * @param code hex code from the address 0x014B in ROM
 * @return string containing the licensee name if it was found
 */
std::string goober::Rom::getLicensee(uint8_t code) {
    std::string licensee;

    if (code == 0x33) {
        // Read directly from bytes 0x0144 and 0x0145
        uint8_t asciiCode[] = {
            bank00[0x0144], bank00[0x0145]
        };
        licensee = reinterpret_cast<const char *>(asciiCode);
    } else {
        licensee = goober::OLD_LICENSEES_MAP[code];
    }

    return licensee;
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
    if (bankIdx >= 1 && bankIdx < romBanks.size()) {
        bankNN = romBanks[bankIdx];
    }
}