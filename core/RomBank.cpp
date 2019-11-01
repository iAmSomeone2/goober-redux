/**
 *  RomBank class for the C++ version of Goober
 *
 *  @author Brenden Davidson <davidson.brenden15@gmail.com>
 *  @date Oct. 31, 2019
 */

#include "RomBank.hpp"

goober::RomBank::RomBank() = default;

goober::RomBank::RomBank(const uint8_t *initData) {
    loadBank(initData);
}

goober::RomBank::RomBank(const char *initData) {
    loadBank(initData);
}

goober::RomBank::RomBank(const std::vector<uint8_t>& initData) {
    loadBank(initData);
}

goober::RomBank::RomBank(const std::vector<char>& initData) {
    loadBank(initData);
}

uint8_t goober::RomBank::read(uint16_t address) {
    return data[address];
}

uint8_t &goober::RomBank::operator[](uint16_t index) {
    return data[index];
}

void goober::RomBank::loadBank(const uint8_t *initData) {
    for (int i = 0; i < ROM_BANK_SIZE; i++) {
        data[i] = initData[i];
    }
}

void goober::RomBank::loadBank(const char *initData) {
    for (int i = 0; i < ROM_BANK_SIZE; ++i) {
        data[i] = static_cast<uint8_t>(initData[i]);
    }
}

void goober::RomBank::loadBank(const std::vector<uint8_t> &initData) {
    for (int i = 0; i < ROM_BANK_SIZE; ++i) {
        data[i] = initData[i];
    }
}

void goober::RomBank::loadBank(const std::vector<char> &initData) {
    for (int i = 0; i < ROM_BANK_SIZE; ++i) {
        data[i] = static_cast<uint8_t>(initData[i]);
    }
}
