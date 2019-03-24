#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/map)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Map-Library")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include/OrderedMap.hpp
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        ${BASE_PATH}/include
)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "OrderedMap-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    Map-Library
    ${GTEST_LIBRARY}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include
)

target_sources(${TARGET_NAME}
    PRIVATE
        OrderedMapMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
