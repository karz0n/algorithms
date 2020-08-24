set(TARGET "Select-Library")

add_library(${TARGET} INTERFACE)
add_library("Select::Library" ALIAS ${TARGET})

target_sources(${TARGET}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Select.hpp
)

target_include_directories(${TARGET}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()