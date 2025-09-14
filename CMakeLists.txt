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
set(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_library(KratosRuntime SHARED
    ${SRC}/test.c
)
target_include_directories(KratosRuntime
    PRIVATE ${SRC}
    PUBLIC ${INC}
)
set_target_properties(KratosRuntime PROPERTIES
    OUTPUT_NAME "KratosRuntime-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${BIN}
    LIBRARY_OUTPUT_DIRECTORY ${BIN}
    ARCHIVE_OUTPUT_DIRECTORY ${BIN}
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