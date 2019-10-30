#ifndef ROM_HXX
#define ROM_HXX

#include <map>
#include <vector>
#include <string>
#include <filesystem>

static const std::filesystem::path OLD_LICENSEES_PATH("./old_licensees.csv");
static const std::filesystem::path CART_TYPE_PATH("./cart_types.csv");

class Rom {
public:
    /**
     * Constructs a Rom object without reading in a ROM file.
     */
    Rom();

    /**
     * Constructs a Rom object and loads in a ROM file.
     */
    Rom(std::filesystem::path romFile);
private:
    // Basic ROM info
    std::map<uint8_t, std::string> OLD_LICENSEE_MAP;
    std::map<uint8_t, std::string> CART_TYPE_MAP;
    uint16_t m_romBanks;
    uint8_t m_ramSize;

    // Special feature flags
    bool m_cgbOnly;
    bool m_sgbSupport;
    bool m_japanOnly;

    // ROM data
    uint8_t *bank00;
    uint8_t *bankNN;
    std::vector<uint8_t> romBanks;

    /**
     * Map containing all possible numbers of ROM banks based on hex value.
     */
    const std::map<const uint8_t, const uint16_t> ROM_BANK_MAP = {
        {0x00, 0}, {0x04, 4}, {0x02, 8}, {0x03, 16}, {0x04, 32},
        {0x05, 64}, {0x06, 128}, {0x07, 256}, {0x08, 512},
        {0x52, 72}, {0x53, 80}, {0x54, 96}
    };

    /**
     * Map for determining how much RAM is needed.
     */
    const std::map<const uint8_t, const uint8_t> RAM_SIZE_MAP = {
        {0x00, 0}, {0x01, 2}, {0x02, 8}, {0x03, 32}, {0x04, 128}, {0x05, 64}
    };

    /**
     * Map for determining if the ROM only works in GameBoy Color mode
     */
    const std::map<const uint8_t, const bool> CGB_FLAG_MAP = {
        {0x80, false}, {0xC0, true}
    };

    /**
     * Map for determining if the ROM has special support for the Super GameBoy
     */
    const std::map<const uint8_t, const bool> SGB_FLAG_MAP = {
        {0x00, false}, {0x30, true}
    };

    /**
     * Map for determining if the ROM is region-locked to Japan
     */
    const std::map<const uint8_t, bool> DEST_CODE_MAP = {
        {0x00, true}, {0x01, false}
    };

    /**
     * Loads the specified ROM into memory.
     * 
     * @param romPath path to the ROM
     */
    void loadRom(std::filesystem::path romPath);

    /**
     * Loads in the specified CSV file and returns a map containg the value pairs.
     * 
     * @param filePath path on the filesystem from which to read the file from
     * @return map containing the value pairs
     */
    static std::map<uint8_t, std::string> loadCsv(std::filesystem::path filePath);

    /**
     * Converts the string representation of a hex number into a standard decimal one.
     * 
     * @param hexStr string containing the hex value to convert
     * @return a byte containing the converted value
     */
    static uint8_t hexStrToUByte(std::string hexStr);

    /**
     * Returns the appropriate licensee based on the value passed in.
     * 
     * @param code hex code from the address 0x014B in ROM
     * @return string containing the licensee name if it was found
     */
    std::string getLicensee(uint8_t code);
};

#endif // ROM_HXX