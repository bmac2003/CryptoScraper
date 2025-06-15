cmake_minimum_required(VERSION 3.10)
project(CryptoScraper C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Find required packages
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)

# Include directories
include_directories(${INC_DIR} ${LIBXML2_INCLUDE_DIRS})

# Manually specify source and test files to avoid glob pitfalls
set(SOURCES
    ${SRC_DIR}/main.c
    ${SRC_DIR}/getUrlData.c
    ${SRC_DIR}/botCreator.c
)
set(TEST_SOURCES
    ${TEST_DIR}/getUrlData.test.c
    ${TEST_DIR}/botCreator.test.c
)

message("Sources: ${SOURCES}")
message("Test Sources: ${TEST_SOURCES}")

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR} ${LIBXML2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# Test executables with custom output directory
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_BASE ${TEST_SRC} NAME_WE)
    string(REGEX REPLACE "\\.test" "" TEST_NAME ${TEST_BASE})
    # Find the corresponding source file
    set(SOURCE_FILE ${SRC_DIR}/${TEST_NAME}.c)
    if(EXISTS ${SOURCE_FILE})
        add_executable(${TEST_NAME}_test ${SOURCE_FILE} ${TEST_SRC})
        # Set output directory for test executables
        set_target_properties(${TEST_NAME}_test PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/tests
        )
        target_include_directories(${TEST_NAME}_test PRIVATE ${INC_DIR} ${LIBXML2_INCLUDE_DIRS})
        target_link_libraries(${TEST_NAME}_test PRIVATE ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
        target_compile_options(${TEST_NAME}_test PRIVATE -Wall -Wextra)
        add_test(NAME ${TEST_NAME}_test COMMAND ${BUILD_DIR}/tests/${TEST_NAME}_test)
        add_custom_target(run_${TEST_NAME}_test
            COMMAND ${BUILD_DIR}/tests/${TEST_NAME}_test
            DEPENDS ${TEST_NAME}_test
            WORKING_DIRECTORY ${BUILD_DIR}/tests
        )
    else()
        message(WARNING "No source file found for test: ${TEST_NAME}")
    endif()
endforeach()

# Ensure build directory exists
file(MAKE_DIRECTORY ${BUILD_DIR})
# Ensure build/tests directory exists
file(MAKE_DIRECTORY ${BUILD_DIR}/tests)
