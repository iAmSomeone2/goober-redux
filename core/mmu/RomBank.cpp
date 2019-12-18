/**
 *  RomBank class for the C++ version of Goober
 *
 *  @author Brenden Davidson <davidson.brenden15@gmail.com>
 *  @date Oct. 31, 2019
 */

#include "RomBank.hpp"

using namespace goober;

RomBank::RomBank() = default;

RomBank::RomBank(const byte *initData) {
    loadBank(initData);
}

RomBank::RomBank(const char *initData) {
    loadBank(initData);
}

RomBank::RomBank(const std::vector<byte>& initData) {
    loadBank(initData);
}

RomBank::RomBank(const std::vector<char>& initData) {
    loadBank(initData);
}

byte RomBank::read(word address) {
    return data[address];
}

byte &RomBank::operator[](word index) {
    return data[index];
}

void RomBank::loadBank(const byte *initData) {
    for (int i = 0; i < ROM_BANK_SIZE; i++) {
        data[i] = initData[i];
    }
}

void RomBank::loadBank(const char *initData) {
    for (int i = 0; i < ROM_BANK_SIZE; ++i) {
        data[i] = static_cast<byte>(initData[i]);
    }
}

void RomBank::loadBank(const std::vector<byte> &initData) {
    for (int i = 0; i < ROM_BANK_SIZE; ++i) {
        data[i] = initData[i];
    }
}

void RomBank::loadBank(const std::vector<char> &initData) {
    for (int i = 0; i < ROM_BANK_SIZE; ++i) {
        data[i] = static_cast<byte>(initData[i]);
    }
}
