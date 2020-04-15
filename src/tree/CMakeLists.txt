#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/tree)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Tree-Library")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include/BinarySearchTree.hpp
        ${BASE_PATH}/include/RedBlackBinarySearchTree.hpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Tree-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "Tree-Library"
    "Tools-Library"
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/TreeTestData.hpp
        ${BASE_PATH}/test/TreeTestData.cpp
        ${BASE_PATH}/test/TreeTest.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
