# Copyright (c) 2025 Soviet-Cat
# See LICENSE.md for details

cmake_minimum_required(VERSION 3.20)

project(KratosRuntime
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Local directories
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BIN ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIB ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Parameter cache
set(KratosRuntimeStatic OFF CACHE BOOL "Wether to build KratosRuntime as a static library. ON - static. OFF - shared.")
set(KratosRuntimeTest OFF CACHE BOOL "Wether to build the test executable for KratosRuntime.")

# Sources
set(KratosRuntimeSources
    ${SRC}/kratos_platform.cpp
)

# Platform dependent sources
list(APPEND KratosRuntimeSources ${SRC}/platforms/${CMAKE_SYSTEM_NAME}.cpp)

# Remove "lib" prefix
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Library type
if(KratosRuntimeStatic)
    add_library(KratosRuntime STATIC ${KratosRuntimeSources})
else()
    add_library(KratosRuntime SHARED ${KratosRuntimeSources})
endif()

# Library properties
set_target_properties(KratosRuntime PROPERTIES
    OUTPUT_NAME KratosRuntime-v${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
    VERSION ${PROJECT_VERSION}
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY ${BIN}
    LIBRARY_OUTPUT_DIRECTORY ${LIB}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB}
)
target_include_directories(KratosRuntime PUBLIC ${INC})

# Exporting
target_compile_definitions(KratosRuntime PRIVATE EXPORTS)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(KratosRuntime PRIVATE WINDOWS)
endif()

# Test executable
add_executable(KratosRuntimeExec ${SRC}/test.cpp)
target_link_libraries(KratosRuntimeExec PRIVATE KratosRuntime)
set_target_properties(KratosRuntimeExec PROPERTIES
    OUTPUT_NAME KratosRuntimeTest-v${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
    VERSION ${PROJECT_VERSION}
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY ${BIN}
    LIBRARY_OUTPUT_DIRECTORY ${LIB}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB}
)
target_include_directories(KratosRuntime PRIVATE ${INC})