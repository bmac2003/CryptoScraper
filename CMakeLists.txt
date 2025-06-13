cmake_minimum_required(VERSION 3.10)
project(CryptoScraper C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Define source directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Find required packages
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)

# Include directories
include_directories(${INC_DIR} ${TEST_DIR})

# Gather source files
file(GLOB SOURCES ${SRC_DIR}/*.c)
file(GLOB TEST_SOURCES ${TEST_DIR}/*.test.c)

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})

# Test executables
foreach(TEST_SRC ${TEST_SOURCES})
    # Get the base name (e.g., scraper.test.c -> scraper)
    get_filename_component(TEST_BASE ${TEST_SRC} NAME_WE)
    string(REGEX REPLACE "\\.test" "" TEST_NAME ${TEST_BASE})

    # Create test executable
    add_executable(${TEST_NAME}_test ${SRC_DIR}/${TEST_NAME}.c ${TEST_SRC})
    target_link_libraries(${TEST_NAME}_test PRIVATE ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})

    # Add test target
    add_test(NAME ${TEST_NAME}_test COMMAND ${TEST_NAME}_test)

    # Custom target to run the test directly
    add_custom_target(run_${TEST_NAME}_test
        COMMAND ${TEST_NAME}_test
        DEPENDS ${TEST_NAME}_test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endforeach()

# Set compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
foreach(TEST_TARGET ${TEST_SOURCES})
    get_filename_component(TEST_BASE ${TEST_TARGET} NAME_WE)
    string(REGEX REPLACE "\\.test" "" TEST_NAME ${TEST_BASE})
    target_compile_options(${TEST_NAME}_test PRIVATE -Wall -Wextra)
endforeach()

# Ensure build directory exists
file(MAKE_DIRECTORY ${BUILD_DIR})
