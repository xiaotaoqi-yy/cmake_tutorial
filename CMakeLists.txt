cmake_minimum_required(VERSION 2.6)
project(Tutorial)

# CMAKE_INSTALL_PREFIX is used to determine
# the root of where the files will be installed
set (CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
message("CIP = ${CMAKE_INSTALL_PREFIX}")
# The version number.
set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    TutorialConfig.h.in
    #"${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

# should we use our own math functions?
option(
    USE_MYMATH
    "Use tutorial provided math implementation" ON)

# Add the binary tree to the search path for include files
# so that we will find the TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# Add the MathFunctions library?
#
if (USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory(MathFunctions)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)

# Add the execuble
add_executable(Tutorial tutorial.cxx)
target_link_libraries(Tutorial ${EXTRA_LIBS})

# Add the install target
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

include(CTest)

# does the application run
add_test (TutorialRuns Tutorial 25)
# does it sqrt of 25
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
# does it handle negative numbers
#add_test (TutorialNegative Tutorial -25)
#set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")
# does it handle small numbers
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

