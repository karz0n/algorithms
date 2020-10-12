set(TARGET "Select-Test")

add_executable(${TARGET} "")

target_link_libraries(${TARGET} PRIVATE Select::Library Tools::Library)

target_include_directories(${TARGET}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/SelectTest.cpp)

target_add_tests(TARGET ${TARGET})
