# CMakeList.txt : CMake project for IAQ, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)


# CMAKE Pin cxx compiler to CXX14 until update to CXX17
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (IAQ LANGUAGES C CXX)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake_modules)

option(IAQ_BUILD_TESTS "build tests alongside the project" ON)
add_subdirectory(IAQ)

# TODO: Add tests and install targets if needed.

if (IAQ_BUILD_TESTS)
    include(CTest)
    find_package(GTest QUIET)
    if (NOT GTEST_FOUND)
    message("GoogleTest not found. Consider installing it on your system. Downloading it from source...")
    include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_SHALLOW true
        )
        set(BUILD_GMOCK OFF CACHE BOOL "")
        FetchContent_GetProperties(googletest)
        if(NOT googletest_POPULATED)
            FetchContent_Populate(googletest)
            add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
        endif()
    endif()
    add_subdirectory(tests)
endif()

message(STATUS INCLUDE_DIRECTORIES=${INCLUDE_DIRECTORIES})
