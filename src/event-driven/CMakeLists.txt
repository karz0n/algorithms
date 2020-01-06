#[[

Dependencies:
    $ sudo apt-get update
    $ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

]]#

#------------------------------------------------------------------------------------------

set(BASE_PATH ${PROJECT_SOURCE_DIR}/src/event-driven)

#------------------------------------------------------------------------------------------

set(TARGET_NAME "EventDriven-Main")

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${TARGET_NAME} "")

set_target_properties(${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

target_link_libraries(${TARGET_NAME}
    "Queue-Library"
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
)

target_sources(${TARGET_NAME}
    PRIVATE
        ${BASE_PATH}/CollisionSystem.cpp
        ${BASE_PATH}/CollisionSystem.hpp
        ${BASE_PATH}/DrawArea.cpp
        ${BASE_PATH}/DrawArea.hpp
        ${BASE_PATH}/DrawObject.cpp
        ${BASE_PATH}/DrawObject.hpp
        ${BASE_PATH}/Event.cpp
        ${BASE_PATH}/Event.hpp
        ${BASE_PATH}/Particle.cpp
        ${BASE_PATH}/Particle.hpp
        ${BASE_PATH}/EventDrivenMain.cpp
)
