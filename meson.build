project('Goober', 'cpp', version: '0.1', default_options: ['cpp_std=c++17'])

# Main include
inc_dir = include_directories('include')

# Dependencies
dep_boost = dependency('Boost', version: '>=1.29.0')

dep_testing = dependency('GTest', required: get_option('enable_testing'))


# Core libs declarations

# MMU static lib 
core_mmu_dir = include_directories('core/mmu')
mmu_sources = [
    'core/mmu/Mmu.cpp', 'core/mmu/Mmu.hpp', 'core/mmu/Ram.cpp', 'core/mmu/Ram.hpp',
    'core/mmu/RamBank.cpp', 'core/mmu/RamBank.hpp', 'core/mmu/Rom.cpp', 'core/mmu/Rom.hpp',
    'core/mmu/RomBank.cpp', 'core/mmu/RomBank.hpp'
]

mmu_lib = static_library('goober-core-mmu', sources: mmu_sources,
    dependencies: dep_boost, include_directories: inc_dir
)

if dep_testing.found()
    # MMU lib test
    mmu_test = executable('mmu-test', sources: ['core/mmu/tests/MmuTest.cpp', 'core/mmu/tests/TestConstants.hpp'],
        link_with: mmu_lib, dependencies: dep_testing, include_directories: inc_dir
    )
    test('core-mmu-test', mmu_test)

    # RAM test
    ram_test = executable('ram-test', sources: ['core/mmu/tests/RamTest.cpp', 'core/mmu/tests/TestConstants.hpp'],
        link_with: mmu_lib, dependencies: dep_testing, include_directories: inc_dir
    )
    test('core-ram-test', ram_test)

    # RAM test
    rom_test = executable('rom-test', sources: ['core/mmu/tests/RomTest.cpp', 'core/mmu/tests/TestConstants.hpp'],
        link_with: mmu_lib, dependencies: dep_testing, include_directories: inc_dir
    )
    test('core-rom-test', rom_test)
endif


# CPU static lib
core_cpu_dir = include_directories('core/cpu')
cpu_sources = [
    'core/cpu/Cpu.cxx', 'core/cpu/Cpu.hxx'
]

cpu_lib = static_library('goober-core-cpu', sources: cpu_sources,
    link_with: mmu_lib, include_directories: inc_dir
)