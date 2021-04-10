set(TARGET "Crypto-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Crypto::Library)

target_include_directories(
    ${TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_sources(
    ${TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/MD5Test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/SHA1Test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/UUIDTest.cpp"
)

target_add_tests(TARGET ${TARGET})
