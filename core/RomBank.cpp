//
// Created by bdavidson on 10/31/19.
//

#include "RomBank.hpp"

goober::RomBank::RomBank() {
    data.resize(16384);
}

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
    for (int i = 0; i < BANK_SIZE; i++) {
        data.push_back(initData[i]);
    }
}

void goober::RomBank::loadBank(const char *initData) {
    for (int i = 0; i < BANK_SIZE; ++i) {
        data.push_back(static_cast<uint8_t>(initData[i]));
    }
}

void goober::RomBank::loadBank(const std::vector<uint8_t> &initData) {
    data = initData;
}

void goober::RomBank::loadBank(const std::vector<char> &initData) {
    for (int i = 0; i < BANK_SIZE; ++i) {
        data.push_back(static_cast<uint8_t>(initData[i]));
    }
}
