#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Brenden Davidson on 11/4/19.
//

#include <gtest/gtest.h>
#include <boost/format.hpp>

#include <random>
#include <chrono>

#include "../Mmu.hpp"

class MMUTest : public ::testing::Test {
protected:
    std::filesystem::path TEST_ROM;
    static const uint16_t START_IDX = 0x0000;
    static const uint16_t ROM_END_IDX = 0x7FFF;
    static const uint16_t RAM_START_IDX = 0x8000;
    static const uint16_t END_IDX = 0xFFFF;
    std::default_random_engine generator;
    std::uniform_int_distribution<uint8_t> distribution{0, UINT8_MAX};

    MMUTest() {
        std::random_device randomDevice;
        auto now = static_cast<uint32_t>(time(0));
        std::seed_seq seed{randomDevice(), now};
        generator.seed(seed);
        TEST_ROM = "/home/bdavidson/roms/gb/Super_Mario_Land.gb";
    }
};

TEST_F(MMUTest, RamReadAndWrite) {
    goober::MMU mmu{TEST_ROM};

    for (int i = RAM_START_IDX; i <= END_IDX; i++) {
        uint8_t testValue = distribution(generator);
        mmu.set(testValue, i);
        ASSERT_EQ(testValue, mmu.get(i)) << boost::format("Failed at address: 0x%04x") %i << std::endl;
    }
}

TEST_F(MMUTest, AttemptToWriteToROM) {
    goober::MMU mmu{TEST_ROM};

    for (int i = START_IDX; i <= ROM_END_IDX; i++) {
        mmu.set(0, i);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop