set(TARGET "Queue-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET}
PRIVATE
    Queue::Library
)

target_include_directories(${TARGET}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${TARGET}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QueueTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PriorityQueueTest.cpp
)

target_add_tests(TARGET ${TARGET})