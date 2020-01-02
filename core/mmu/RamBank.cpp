#include "RamBank.hpp"

using namespace goober;

RamBank::RamBank() {
    data.resize(4096);
}

RamBank::RamBank(const int& bankSize) {
    data.resize(bankSize);
}

void RamBank::setSize(const int& bankSize) {
    data.resize(bankSize);
}

byte &RamBank::operator[](const mem_loc& index) {
    return data.at(index);
}

byte RamBank::get(const mem_loc& index) {
    return data.at(index);
}

void RamBank::set(const byte& value, const mem_loc& index) {
    data.at(index) = value;
}