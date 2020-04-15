include(GoogleTest)

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/sort)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Sort-Library")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include/BottomUpMerge.hpp
        ${BASE_PATH}/include/Insertion.hpp
        ${BASE_PATH}/include/Merge.hpp
        ${BASE_PATH}/include/Quick.hpp
        ${BASE_PATH}/include/Selection.hpp
        ${BASE_PATH}/include/Shell.hpp
        ${BASE_PATH}/include/ThreeWayQuick.hpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Sort-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
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
        ${BASE_PATH}/test/BottomUpMergeTest.cpp
        ${BASE_PATH}/test/HeapSortTest.cpp
        ${BASE_PATH}/test/InsertionTest.cpp
        ${BASE_PATH}/test/MergeTest.cpp
        ${BASE_PATH}/test/QuickTest.cpp
        ${BASE_PATH}/test/SelectionTest.cpp
        ${BASE_PATH}/test/ShellTest.cpp
        ${BASE_PATH}/test/ThreeWayQuickTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
