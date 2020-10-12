list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

include(BuildLocation)
include(BuildType)
include(EnableCcache)

include(CxxTestCompiler)
checkforcxx17compiler(CXX17_COMPILER)
if(CXX17_COMPILER)
    enablecxx17()
else()
    message(FATAL_ERROR "The C++17 standard not supported")
endif()

if(ALG_ENABLE_TESTS)
    include(AddGoogleTest)
endif()
