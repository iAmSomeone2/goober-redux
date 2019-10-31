set(SOURCES Rom.cxx Rom.hxx RomBank.cpp RomBank.hpp)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(goober-core STATIC ${SOURCES})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    target_link_libraries(rom-test PUBLIC GTest::GTest GTest::Main)
    target_link_libraries(rom-test PUBLIC goober-core)

    add_test(
        NAME 
            TestRomObject
        COMMAND
            test-rom
        )
endif()