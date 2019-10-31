set(SOURCES Rom.cxx Rom.hxx)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(goober-core STATIC ${SOURCES})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    target_link_libraries(test-rom PUBLIC goober-core)

    add_test(
        NAME 
            TestRomObject
        COMMAND
            test-rom
        )
endif()