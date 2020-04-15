include(GoogleTest)

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/stack)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Stack-Library")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include/Stack.hpp
        ${BASE_PATH}/include/LinkedStack.hpp
        ${BASE_PATH}/include/FixedArrayStack.hpp
        ${BASE_PATH}/include/ResizableArrayStack.hpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Stack-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "Stack-Library"
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/StackTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Stack-Evaluator")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "Stack-Library"
    GTest::gtest
    GTest::gtest_main
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/ArithmeticEvaluator.hpp
        ${BASE_PATH}/src/ArithmeticEvaluator.cpp
        ${BASE_PATH}/test/ArithmeticEvaluatorTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
