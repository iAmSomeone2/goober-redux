//
// Created by bdavidson on 10/31/19.
//

#include <filesystem>

#include <gtest/gtest.h>

#include "../Rom.hxx"

class RomTest : public ::testing::Test {
};

TEST_F(RomTest, OpenRomWithDefaultConstructor) {
    const std::filesystem::path test_rom = "/run/media/bdavidson/Linux_Data/retropie/roms/gb/Super_Mario_Land.gb";
    goober::Rom rom;
    rom.loadRom(test_rom);
}

TEST_F(RomTest, OpenRomInConstructor) {
    const std::filesystem::path test_rom = "/run/media/bdavidson/Linux_Data/retropie/roms/gb/Super_Mario_Land.gb";
    goober::Rom rom(test_rom);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}