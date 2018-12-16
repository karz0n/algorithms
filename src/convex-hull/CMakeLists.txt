#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/convex-hull)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "ConvexHull-Main")

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    List-Library
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/Point.hpp
        ${BASE_PATH}/Comparators.hpp
        ${BASE_PATH}/Comparators.cpp
        ${BASE_PATH}/ConvexHull.hpp
        ${BASE_PATH}/ConvexHull.cpp
        ${BASE_PATH}/ConvexHullMain.cpp
)

add_test(
    NAME
        ${TARGET_NAME}
    COMMAND
        ${TARGET_NAME}
    WORKING_DIRECTORY
        ${PROJECT_OUTPUT_DIR}
)
