#------------------------------------------------------------------------------
# Targets Configuration
#------------------------------------------------------------------------------

set(TARGET_NAME "list")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    ${GTEST_LIBRARY}
    ${GMOCK_LIBRARY}
)

target_sources(${TARGET_NAME}
    PRIVATE
        "Node.hpp"
        "List.hpp"
        "LinkedList.hpp"
        "ListMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

