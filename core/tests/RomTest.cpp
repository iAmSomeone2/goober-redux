//
// Created by bdavidson on 10/31/19.
//

#include <filesystem>

#include <gtest/gtest.h>

#include "../Rom.hpp"

class RomTest : public ::testing::Test {
protected:
    std::filesystem::path testRom;
    std::string expectedTitle;
    std::string expectedLicensee;

    RomTest() {
        testRom = "/home/bdavidson/roms/gb/Super_Mario_Land.gb";
        expectedTitle = "SUPER MARIOLAND";
        expectedLicensee = "nintendo";
    }
};

TEST_F(RomTest, OpenRomWithDefaultConstructor) {
    std::cout << "Running test `Open Rom with default constructor`..." << std::endl;
    goober::Rom rom;
    rom.loadRom(testRom);
    ASSERT_STREQ(rom.getTitle().c_str(), expectedTitle.c_str());
    ASSERT_STREQ(rom.getLicensee().c_str(), expectedLicensee.c_str());
}

TEST_F(RomTest, OpenRomInConstructor) {
    std::cout << "Running test `Open Rom in constructor`..." << std::endl;
    goober::Rom rom(testRom);
    ASSERT_STREQ(rom.getTitle().c_str(), expectedTitle.c_str());
    ASSERT_STREQ(rom.getLicensee().c_str(), expectedLicensee.c_str());
}

TEST_F(RomTest, RomDoesNotExist) {
    std::cout << "Running test `Rom does not exist`..." << std::endl;
    goober::Rom rom;
    ASSERT_THROW(rom.loadRom(""), std::runtime_error);
    ASSERT_STREQ(rom.getTitle().c_str(), "UNDEFINED");
    ASSERT_STREQ(rom.getLicensee().c_str(), "UNDEFINED");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}