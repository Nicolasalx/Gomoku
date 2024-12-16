cmake_minimum_required(VERSION 3.15)
project(pbrain-gomoku-ai LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE release CACHE STRING "Build type" FORCE)
endif()

set(COMPILER_WARNINGS -Wall -Wextra)
set(OPTIMIZATION_FLAGS -O2)
set(DEBUG_FLAGS -O2 -DGOMOKU_DEBUG)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_WARNINGS /W4)
    set(OPTIMIZATION_FLAGS /O2)
    set(DEBUG_FLAGS /O2 /DGOMOKU_DEBUG)
endif()

file(GLOB_RECURSE SRC_FILES src/*.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_WARNINGS} ${OPTIMIZATION_FLAGS})
if(CMAKE_BUILD_TYPE STREQUAL "release")
    target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_WARNINGS} ${OPTIMIZATION_FLAGS})
elseif(CMAKE_BUILD_TYPE STREQUAL "debug")
    target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_WARNINGS} ${DEBUG_FLAGS})
endif()

add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Building debug mode")
    
add_custom_target(profiling
    COMMAND ${CMAKE_COMMAND} -DCMAKE_CXX_FLAGS=-pg ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Building profiling mode")
