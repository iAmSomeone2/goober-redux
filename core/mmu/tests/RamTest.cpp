//
// Created by bdavidson on 11/3/19.
//

#include <gtest/gtest.h>
#include <boost/format.hpp>

#include <random>
#include <chrono>

#include "../Ram.hpp"

class RamTest : public ::testing::Test {
protected:
    static const uint16_t START_IDX = 0x8000;
    static const uint16_t END_IDX = 0xFFFF;
    std::default_random_engine generator;
    std::uniform_int_distribution<uint8_t> distribution{33, 126};

    goober::Ram ram;

    RamTest() {
        std::random_device randomDevice;
        auto now = static_cast<uint32_t>(time(0));
        std::seed_seq seed{randomDevice(), now};
        generator.seed(seed);
    }
};

TEST_F(RamTest, ReadAndWriteAllRAM) {
    for (int i = START_IDX; i <= END_IDX; i++) {
        uint8_t testVal = distribution(generator);
        ram.set(testVal, i);
        ASSERT_EQ(testVal, ram.get(i)) << boost::format("Problem at address: 0x%04X") % i << std::endl;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}