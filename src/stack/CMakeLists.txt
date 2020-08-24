set(TARGET "Stack-Library")

add_library(${TARGET} INTERFACE)
add_library("Stack::Library" ALIAS ${TARGET})

target_sources(${TARGET}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Stack.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/LinkedStack.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FixedArrayStack.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ResizableArrayStack.hpp
)

target_include_directories(${TARGET}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()