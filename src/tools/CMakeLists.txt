#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/tools)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Tools-Library")

add_library(${TARGET_NAME}  )

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Tools.hpp
        ${BASE_PATH}/include/Common.hpp
        ${BASE_PATH}/include/RandomGenerator.hpp
        ${BASE_PATH}/Common.cpp
        ${BASE_PATH}/RandomGenerator.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include
)
