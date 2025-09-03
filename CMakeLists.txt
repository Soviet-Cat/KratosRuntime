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
set(INC ${CMAKE_CURRENT_BINARY_DIR}/include)
set(BIN ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIB ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Parameter cache
set(KratosRuntimeStatic OFF CACHE BOOL "Wether to build KratosRuntime as a static library. ON - static. OFF - shared.")

# Sources
set(KratosRuntimeSources 
    
)

# Library type
if(KratosRuntimeStatic)
    add_library(KratosRuntime STATIC ${KratosRuntimeSources})
else()
    add_library(KratosRuntime SHARED ${KratosRuntimeSources})
endif()

# Remove "lib" prefix
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Library properties
set_target_properties(KratosRuntime PROPERTIES
    OUTPUT_NAME KratosRuntime-v${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
    VERSION ${PROJECT_VERSION}
    RUNTIME_OUTPUT_DIRECTORY ${BIN}
    LIBRARY_OUTPUT_DIRECTORY ${LIB}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB}
)