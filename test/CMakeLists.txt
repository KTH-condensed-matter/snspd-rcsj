# Based on https://github.com/lefticus/cpp_starter_project by lefticus (Jason Turner)

# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()


add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Add project sources except for main.cpp
file(GLOB_RECURSE PROJECT_SOURCES "../src/*.cpp")
list(REMOVE_ITEM PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")

add_executable(tests ${TEST_SOURCES} ${PROJECT_SOURCES})
target_link_libraries(tests PRIVATE project_warnings project_options catch_main ${CONAN_TARGETS})

# automatically discover tests that are defined in catch based test files you
# can modify the unittests. TEST_PREFIX to whatever you want, or use different
# for different binaries
catch_discover_tests(
        tests
        TEST_PREFIX
        "unittests."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=tests.xml)
