
set(SOURCES Rom.cpp Rom.hpp RomBank.cpp RomBank.hpp Ram.cpp Ram.hpp)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(goober-core STATIC ${SOURCES})
set_target_properties(goober-core PROPERTIES VERISION ${PROJECT_VERSION})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    if(BUILD_TESTING STREQUAL ON)
        target_link_libraries(rom-test PUBLIC GTest::GTest GTest::Main)
        target_link_libraries(rom-test PUBLIC goober-core)

        add_test(
            NAME
                TestRomObject
            COMMAND
                test-rom
            )
    endif()
endif()