dep_testing = disabler()
if get_option('enable_testing')
    dep_testing = dependency('GTest')
endif

# Core libs declarations

# MMU static lib 
core_mmu_dir = include_directories('mmu')
mmu_sources = [
    'mmu/Mmu.cpp', 'mmu/Mmu.hpp', 'mmu/Ram.cpp', 'mmu/Ram.hpp',
    'mmu/RamBank.cpp', 'mmu/RamBank.hpp', 'mmu/Rom.cpp', 'mmu/Rom.hpp',
    'mmu/RomBank.cpp', 'mmu/RomBank.hpp'
]

mmu_lib = static_library('goober-core-mmu', sources: mmu_sources,
    dependencies: dep_boost, include_directories: inc_dir
)

if dep_testing.found()
    # MMU lib test
    mmu_test = executable('mmu-test', sources: ['mmu/tests/MmuTest.cpp', 'mmu/tests/TestConstants.hpp'],
        link_with: mmu_lib, dependencies: dep_testing, include_directories: inc_dir
    )
    test('core-mmu-test', mmu_test)

    # RAM test
    ram_test = executable('ram-test', sources: ['mmu/tests/RamTest.cpp', 'mmu/tests/TestConstants.hpp'],
        link_with: mmu_lib, dependencies: dep_testing, include_directories: inc_dir
    )
    test('core-ram-test', ram_test)

    # RAM test
    rom_test = executable('rom-test', sources: ['mmu/tests/RomTest.cpp', 'mmu/tests/TestConstants.hpp'],
        link_with: mmu_lib, dependencies: dep_testing, include_directories: inc_dir
    )
    test('core-rom-test', rom_test)
endif


# CPU static lib
core_cpu_dir = include_directories('cpu')
cpu_sources = [
    'cpu/Cpu.cxx', 'cpu/Cpu.hxx'
]

cpu_lib = static_library('goober-core-cpu', sources: cpu_sources,
    link_with: mmu_lib, include_directories: inc_dir
)