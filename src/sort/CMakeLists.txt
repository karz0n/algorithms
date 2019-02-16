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

set(TARGET_NAME "Selection-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Selection.hpp
        ${BASE_PATH}/SelectionMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Insertion-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Insertion.hpp
        ${BASE_PATH}/InsertionMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Shell-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Shell.hpp
        ${BASE_PATH}/ShellMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Merge-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Merge.hpp
        ${BASE_PATH}/MergeMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "BottomUpMerge-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/BottomUpMerge.hpp
        ${BASE_PATH}/BottomUpMergeMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Quick-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Quick.hpp
        ${BASE_PATH}/QuickMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "ThreeWayQuick-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/ThreeWayQuick.hpp
        ${BASE_PATH}/ThreeWayQuickMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "HeapSort-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Tools-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/HeapSort.hpp
        ${BASE_PATH}/HeapSortMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
