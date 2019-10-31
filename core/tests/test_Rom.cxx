#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <Core.hxx>

static std::filesystem::path SUPER_MARIO_LAND("/run/media/bdavidson/Linux_Data/retropie/roms/gb/Super_Mario_Land.gb");

TEST_CASE("Load ROM file in basic Rom object", "[rom]") {
    goober::Rom rom;
    //REQUIRE_THROWS( rom->loadRom(""), "Failed to open ROM file." );
    REQUIRE_NOTHROW( rom.loadRom(SUPER_MARIO_LAND) );
}

TEST_CASE("Load ROM file in overload Rom object", "[rom]") {
    goober::Rom rom(SUPER_MARIO_LAND);
}