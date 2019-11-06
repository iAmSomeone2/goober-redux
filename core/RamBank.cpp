#include "RamBank.hpp"

goober::RamBank::RamBank() {
    data.resize(4096);
}

goober::RamBank::RamBank(int bankSize) {
    data.resize(bankSize);
}

void goober::RamBank::setSize(int bankSize) {
    data.resize(bankSize);
}

uint8_t &goober::RamBank::operator[](uint16_t index) {
    return data.at(index);
}

uint8_t goober::RamBank::get(uint16_t index) {
    return data.at(index);
}

void goober::RamBank::set(uint8_t value, uint16_t index) {
    data.at(index) = value;
}