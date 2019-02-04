#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/tools)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "Tools-Library")

add_library(${TARGET_NAME}  )

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/include/Sequence.hpp
        ${BASE_PATH}/Sequence.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${BASE_PATH}/include
)
