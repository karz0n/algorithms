set(TARGET "Compression-Library" "")

add_library(${TARGET})
add_library("Compression::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Huffman.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/Lzw.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Huffman.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Lzw.cpp")

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC Tools::Library String::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()