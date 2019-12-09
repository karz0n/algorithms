include(GoogleTest)

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/tools)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Tools-Library")

add_library(${TARGET_NAME})

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Sequence.hpp
        ${BASE_PATH}/src/Sequence.cpp
        ${BASE_PATH}/include/CsvFileHandler.hpp
        ${BASE_PATH}/src/CsvFileHandler.cpp
        ${BASE_PATH}/include/CsvFileReader.hpp
        ${BASE_PATH}/src/CsvFileReader.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Tools-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "Tools-Library"
    "googletest-gtest"
    "googletest-gmock"
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/CsvFileReaderTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
