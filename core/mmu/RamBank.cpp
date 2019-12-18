#include "RamBank.hpp"

using namespace goober;

RamBank::RamBank() {
    data.resize(4096);
}

RamBank::RamBank(int bankSize) {
    data.resize(bankSize);
}

void RamBank::setSize(int bankSize) {
    data.resize(bankSize);
}

byte &RamBank::operator[](word index) {
    return data.at(index);
}

byte RamBank::get(word index) {
    return data.at(index);
}

void RamBank::set(byte value, word index) {
    data.at(index) = value;
}