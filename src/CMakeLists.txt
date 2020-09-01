# Get sources and headers
file(GLOB_RECURSE PROJECT_SOURCES "*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "*.h")

# Add executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE project_options project_warnings
        CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::boost_filesystem CONAN_PKG::boost_program_options)

include(cmake/AddIndicators.cmake)