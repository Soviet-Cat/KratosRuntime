#!/bin/bash

CONFIGURE_OPTIONS="$1"
BUILD_OPTIONS="$2"
INSTALL_OPTIONS="$3"

CMAKE_SYSTEM_NAME=""
CMAKE_SYSTEM_PROCESSOR=""
CMAKE_BUILD_TYPE=""
PROJECT_VERSION=""

clean() {
    rm -rf build
    rm -rf bin
    rm -rf lib
    rm -rf install
}

configure() {
    cmake -S . -B build $CONFIGURE_OPTIONS
}

build() {
    cmake --build build $BUILD_OPTIONS
}

install() {
    cmake --install build --prefix install $INSTALL_OPTIONS
}

cache() {
    cache() {
    cmake -LAH -B build > build/cache.cmake
    while IFS= read -r line; do
        key=$(echo "$line" | cut -d':' -f1 | xargs)
        value=$(echo "$line" | grep -oP '(?<=:STRING=).*')
        case "$key" in
            "PROJECT_VERSION") PROJECT_VERSION="$value" ;;
            "CMAKE_BUILD_TYPE") CMAKE_BUILD_TYPE="$value" ;;
            "CMAKE_SYSTEM_NAME") CMAKE_SYSTEM_NAME="$value" ;;
            "CMAKE_SYSTEM_PROCESSOR") CMAKE_SYSTEM_PROCESSOR="$value" ;;
        esac
    done < build/cache.cmake
}
}

package() {
    mkdir -p release
    ZIP_NAME="KratosRuntime-${PROJECT_VERSION}-${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}.zip"
    (cd install && zip -r "../release/$ZIP_NAME" .)
}

clean
configure
build
install
cache
package