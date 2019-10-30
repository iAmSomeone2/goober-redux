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

Rom::Rom() {
    // Load in the csv files
    OLD_LICENSEE_MAP = loadCsv(OLD_LICENSEES_PATH);
    CART_TYPE_MAP = loadCsv(CART_TYPE_PATH);
}
 
std::map<uint8_t, std::string> Rom::loadCsv(std::filesystem::path filePath) {
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

    std::map<uint8_t, std::string> valueMap;

    // Split each line, convert the hex values, and store the results in the return map
    for (const std::string& line : lines) {
        // Find the comma
        uint32_t commaIdx = static_cast<uint32_t>(line.find(',', 0));
        std::string hexCode = line.substr(0, commaIdx);
        std::string strValue = line.substr(commaIdx);

        uint8_t hexVal = static_cast<uint8_t>(std::stoul(hexCode, nullptr, 16));
        valueMap[hexVal] = strValue;
    }

    return valueMap;
}