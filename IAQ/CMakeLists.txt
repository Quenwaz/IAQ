﻿file(GLOB_RECURSE SOURCES *.cpp *.cc)
file (GLOB_RECURSE INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/iaq/*.hpp" "${PROJECT_SOURCE_DIR}/include/utility/*.hpp")
message(STATUS "INCLUDE_FILES=${INCLUDE_FILES}")
set(SOURCE_FILES ${SOURCES}  ${INCLUDE_FILES})
set(${PROJECT_NAME}_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../include)


add_library(${PROJECT_NAME} OBJECT ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDE})

add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
target_link_libraries(${PROJECT_NAME}_static PRIVATE ${CMAKE_REQUIRED_LIBRARIES})
target_include_directories(${PROJECT_NAME}_static PUBLIC ${${PROJECT_NAME}_INCLUDE})

if(UNIX)
    string(REGEX MATCH ".*/" CXX_COMPILER_DIR ${CMAKE_CXX_COMPILER})
    string(REGEX MATCH ".*[^bin/]" CXX_COMPILER_DIR ${CXX_COMPILER_DIR})
    message(STATUS CXX_COMPILER_DIR=${CXX_COMPILER_DIR})
    target_link_options(${PROJECT_NAME}_static PUBLIC "-Wl,-rpath=${CXX_COMPILER_DIR}/lib64")
endif(UNIX)

set_target_properties(${PROJECT_NAME}_static PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
)