#------------------------------------------------------------------------------
# Targets Configuration
#------------------------------------------------------------------------------

set(TARGET_NAME "selection")

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
        "Sort.hpp"
        "Selection.hpp"
        "SelectionMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------
# Targets Configuration
#------------------------------------------------------------------------------

set(TARGET_NAME "insertion")

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
        "Sort.hpp"
        "Insertion.hpp"
        "InsertionMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------
# Targets Configuration
#------------------------------------------------------------------------------

set(TARGET_NAME "shell")

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
        "Sort.hpp"
        "Shell.hpp"
        "ShellMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
