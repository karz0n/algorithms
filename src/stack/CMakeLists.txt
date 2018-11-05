#------------------------------------------------------------------------------
# Targets Configuration
#------------------------------------------------------------------------------

#---------------------
# Stack Target
#---------------------

set(TARGET_NAME "stack")

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
        "Stack.hpp"
        "LinkedStack.hpp"
        "FixedArrayStack.hpp"
        "ResizableArrayStack.hpp"
        "StackMain.cpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#---------------------
# Evaluator target
#---------------------

set(TARGET_NAME "evaluator")

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
        "ArithmeticEvaluator.hpp"
        "ArithmeticEvaluator.cpp"
        "ArithmeticEvaluationMain.cpp"
        "Stack.hpp"
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
