@echo off
setlocal enabledelayedexpansion

set "CONFIGURE_OPTIONS=%1"
set "BUILD_OPTIONS=%2"
set "INSTALL_OPTIONS=%3"
set "CMAKE_SYSTEM_NAME="
set "CMAKE_SYSTEM_PROCESSOR="
set "CMAKE_BUILD_TYPE="
set "PROJECT_VERSION="

call :clean
call :configure
call :build
call :install
call :cache
call :package

exit /b

:clean
if exist "%CD%\build" rmdir /s /q "%CD%\build"
if exist "%CD%\bin" rmdir /s /q "%CD%\bin"
if exist "%CD%\lib" rmdir /s /q "%CD%\lib"
if exist "%CD%\install" rmdir /s /q "%CD%\install"

:configure
call cmake -S . -B build %CONFIGURE_OPTIONS%
exit /b

:build
call cmake --build build %BUILD_OPTIONS%
exit /b

:install
call cmake --install build --prefix install %INSTALL_OPTIONS%
exit /b

:cache
call cmake -LAH -B build > %CD%\build\cache.cmake
for /f "usebackq tokens=1* delims=: " %%A in ("%CD%/build\cache.cmake") do (
    for /f "tokens=1* delims==" %%C in ("%%B") do (
        if /i "%%A"=="PROJECT_VERSION" set "PROJECT_VERSION=%%D"
        if /i "%%A"=="CMAKE_BUILD_TYPE" set "CMAKE_BUILD_TYPE=%%D"
        if /i "%%A"=="CMAKE_SYSTEM_NAME" set "CMAKE_SYSTEM_NAME=%%D"
        if /i "%%A"=="CMAKE_SYSTEM_PROCESSOR" set "CMAKE_SYSTEM_PROCESSOR=%%D"
    )
)
exit /b

:package
if not exist "%CD%\release" mkdir "%CD%\release"
powershell -Command "Compress-Archive -Force -Path '%CD%\install\*' -DestinationPath '%CD%\release\KratosRuntime-%PROJECT_VERSION%-%CMAKE_BUILD_TYPE%-%CMAKE_SYSTEM_NAME%-%CMAKE_SYSTEM_PROCESSOR%.zip'"
exit /b

:help
echo Usage: %~n0 "configure options" "build options" "install options"
exit /b