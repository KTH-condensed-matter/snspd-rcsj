# Based on https://github.com/lefticus/cpp_starter_project by lefticus (Jason Turner)

include(../cmake/Conan.cmake)
run_conan()

# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()


add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE project_warnings project_options
        catch_main)


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
