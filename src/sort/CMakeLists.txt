#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/sort)

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

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Sort.hpp
        ${BASE_PATH}/Selection.hpp
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

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Sort.hpp
        ${BASE_PATH}/Insertion.hpp
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

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Sort.hpp
        ${BASE_PATH}/Shell.hpp
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

set(TARGET_NAME "Shuffle-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    ${GTEST_LIBRARY}
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Sort.hpp
        ${BASE_PATH}/Shuffle.hpp
        ${BASE_PATH}/ShuffleMain.cpp
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

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Sort.hpp
        ${BASE_PATH}/Merge.hpp
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

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Sort.hpp
        ${BASE_PATH}/BottomUpMerge.hpp
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
