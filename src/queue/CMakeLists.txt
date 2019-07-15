include(GoogleTest)

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/queue)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Queue-Library")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include/Queue.hpp
        ${BASE_PATH}/include/LinkedQueue.hpp
        ${BASE_PATH}/include/ResizableArrayQueue.hpp
        ${BASE_PATH}/include/PriorityQueue.hpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Queue-Test")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    ${GTEST_LIBRARY}
    "Queue-Library"
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/test/QueueTest.cpp
        ${BASE_PATH}/test/PriorityQueueTest.cpp
)

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
