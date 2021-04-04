set(TARGET "Tools-Library")

add_library(${TARGET})
add_library("Tools::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Sequence.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/CsvFileReader.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/MemoryStreamBuffer.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DynamicBitSet.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/CsvFileHandler.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/CsvFileHandler.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/CsvFileReader.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/MemoryStreamBuffer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/DynamicBitSet.cpp")

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()
