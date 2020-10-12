include(FeatureSummary)

option(ALG_ENABLE_TESTS "Enable testing" ON)
add_feature_info(ALG_ENABLE_TESTS ALG_ENABLE_TESTS "Build project with tests")

#[[
# Dependencies:
# $ sudo apt-get update
# $ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
#]]
option(ALG_ENABLE_EVENT_DRIVEN "Enable event driven part of project" OFF)
add_feature_info(ALG_ENABLE_EVENT_DRIVEN ALG_ENABLE_EVENT_DRIVEN
        "Build project with event driven part")

feature_summary(WHAT ALL)
