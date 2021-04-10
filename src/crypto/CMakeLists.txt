set(TARGET "Crypto-Library" "")

add_library(${TARGET})
add_library("Crypto::Library" ALIAS ${TARGET})

target_sources(
    ${TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/Digest.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/DigestMethod.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/MD5.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/SHA1.hpp"
           "${CMAKE_CURRENT_SOURCE_DIR}/include/UUID.hpp"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Digest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/MD5.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/SHA1.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/UUID.cpp")

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TARGET} PUBLIC Tools::Library)

if(ALG_ENABLE_TESTS)
    add_subdirectory(test)
endif()