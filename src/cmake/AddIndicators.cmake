include(ExternalProject)

ExternalProject_Add(
        indicators
        PREFIX ${CMAKE_BINARY_DIR}/lib/indicators
        GIT_REPOSITORY https://github.com/p-ranav/indicators.git
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD OFF
)
ExternalProject_Get_Property(indicators source_dir)
set(INDICATORS_INCLUDE_DIRS ${source_dir}/include)

add_dependencies(${PROJECT_NAME} indicators)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${INDICATORS_INCLUDE_DIRS})