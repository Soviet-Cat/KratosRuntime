cmake_minimum_required(VERSION 3.20)

project(KratosRuntime
    LANGUAGES C
    VERSION 1.0.0
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(PROJECT_VERSION ${PROJECT_VERSION} CACHE STRING "Project version")
set(CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} CACHE STRING "CMake system name")
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR} CACHE STRING "CMake system processor")
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "CMake build type")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMake build type" FORCE)
endif()

include(CMakePackageConfigHelpers)

add_library(KratosRuntime SHARED
    ${SRC}/test.c
)
set_target_properties(KratosRuntime PROPERTIES
    OUTPUT_NAME "KratosRuntime"
    VERSION ${PROJECT_VERSION}
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${BIN}
    LIBRARY_OUTPUT_DIRECTORY ${LIB}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB}
)
target_compile_definitions(KratosRuntime
    PRIVATE KRATOS_EXPORT
)
target_include_directories(KratosRuntime
    PRIVATE ${INC}
    PUBLIC $<BUILD_INTERFACE:${INC}> $<INSTALL_INTERFACE:include>
)
install(
    TARGETS KratosRuntime
    EXPORT KratosRuntimeTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(
    DIRECTORY include/
    DESTINATION include/Kratos
    FILES_MATCHING PATTERN "*.h"
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/KratosRuntimeConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/KratosRuntimeConfig.cmake
    INSTALL_DESTINATION lib/cmake/Kratos
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/KratosRuntimeConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/KratosRuntimeConfigVersion.cmake
    DESTINATION lib/cmake/Kratos
)
install(
    EXPORT KratosRuntimeTargets
    FILE KratosRuntimeTargets.cmake
    NAMESPACE KratosRuntime::
    DESTINATION lib/cmake/Kratos
)


add_executable(KratosRuntimeTest
    ${TEST}/main.c
)
target_link_libraries(KratosRuntimeTest PRIVATE KratosRuntime)
set_target_properties(KratosRuntimeTest PROPERTIES
    OUTPUT_NAME "KratosRuntimeTest-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${BIN}
    LIBRARY_OUTPUT_DIRECTORY ${BIN}
    ARCHIVE_OUTPUT_DIRECTORY ${BIN}
)