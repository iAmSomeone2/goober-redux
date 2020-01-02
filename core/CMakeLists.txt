# MMU library
set(MMU_SOURCES
    mmu/Rom.cpp mmu/Rom.hpp
    mmu/RomBank.cpp mmu/RomBank.hpp
    mmu/Ram.cpp mmu/Ram.hpp
    mmu/RamBank.cpp mmu/RamBank.hpp
    mmu/Mmu.cpp mmu/Mmu.hpp)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(mmu/tests)
endif()

find_package(Boost 1.29 REQUIRED)

add_library(goober-core-mmu STATIC ${MMU_SOURCES})
target_compile_features(goober-core-mmu PRIVATE cxx_auto_type cxx_range_for)
set_target_properties(goober-core-mmu PROPERTIES VERISION ${PROJECT_VERSION})

target_include_directories(goober-core-mmu PRIVATE SYSTEM ${Boost_INCLUDE_DIRS})

# CPU library

set(CPU_SOURCES
    cpu/Cpu.cxx cpu/Cpu.hxx
    cpu/opfuncs.cxx cpu/opfuncs.hxx
)

add_library(goober-core-cpu STATIC ${CPU_SOURCES})
set_target_properties(goober-core-cpu PROPERTIES VERSION ${PROJECT_VERSION})

target_link_libraries(goober-core-cpu PRIVATE goober-core-mmu)
target_include_directories(goober-core-cpu PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Testing setup 
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    if(BUILD_TESTING STREQUAL ON)

        # ROM test setup
        target_link_libraries(rom-test PUBLIC GTest::GTest GTest::Main)
        target_link_libraries(rom-test PUBLIC goober-core-mmu)

        add_test(
            NAME
                TestRomObject
            COMMAND
                rom-test
            )

        # RAM test setup
        target_link_libraries(ram-test PUBLIC GTest::GTest GTest::Main)
        target_link_libraries(ram-test PUBLIC goober-core-mmu)
        target_include_directories(ram-test PRIVATE SYSTEM ${Boost_INCLUDE_DIRS})

        add_test(
            NAME
                TestRamObject
            COMMAND
                ram-test
        )

        # MMU test setup
        target_link_libraries(mmu-test PUBLIC GTest::GTest GTest::Main)
        target_link_libraries(mmu-test PUBLIC goober-core-mmu)
        target_include_directories(mmu-test PRIVATE SYSTEM ${Boost_INCLUDE_DIRS})

        add_test(
            NAME
                TestMmuObject
            COMMAND
                mmu-test
        )
    endif()
endif()
