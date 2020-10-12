set(TARGET "Queue-Library")

add_library(${TARGET} INTERFACE)
add_library("Queue::Library" ALIAS ${TARGET})

target_sources(${TARGET}
        INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Queue.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/LinkedQueue.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ResizableArrayQueue.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/PriorityQueue.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/IndexPriorityQueue.hpp"
        )

target_include_directories(${TARGET}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()