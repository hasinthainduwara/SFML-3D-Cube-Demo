@echo off
echo ========================================
echo   3D Rotating Cube - Build Script
echo ========================================
echo.

:: Check if CMake is available
cmake --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: CMake not found in PATH
    echo Please install CMake from https://cmake.org/download/
    echo.
    pause
    exit /b 1
)

:: Check if Ninja is available
ninja --version >nul 2>&1
if errorlevel 1 (
    echo INFO: Ninja not found, using Visual Studio generator
    set GENERATOR=windows
    set BUILD_DIR=out/build/windows
) else (
    echo INFO: Ninja found, using Ninja generator
    set GENERATOR=x64-debug
    set BUILD_DIR=out/build/x64-debug
)

echo.
echo Building with %GENERATOR% generator...
echo.

:: Configure the project
echo [1/3] Configuring project...
cmake --preset %GENERATOR%
if errorlevel 1 (
    echo ERROR: CMake configuration failed
    echo.
    pause
    exit /b 1
)

:: Build the project
echo [2/3] Building project...
cmake --build %BUILD_DIR%
if errorlevel 1 (
    echo ERROR: Build failed
    echo.
    pause
    exit /b 1
)

:: Find the executable
if "%GENERATOR%"=="windows" (
    set EXE_PATH=%BUILD_DIR%\CMakeProject1.exe
) else (
    set EXE_PATH=%BUILD_DIR%\CMakeProject1\CMakeProject1.exe
)

:: Check if executable exists
if exist "%EXE_PATH%" (
    echo [3/3] Build successful!
    echo.
    echo Executable created at: %EXE_PATH%
    echo.
    
    :: Ask if user wants to run the application
    set /p RUN_APP="Do you want to run the application now? (y/n): "
    if /i "%RUN_APP%"=="y" (
        echo.
        echo Starting 3D Rotating Cube...
        start "" "%EXE_PATH%"
    )
) else (
    echo ERROR: Executable not found at expected location
    echo Expected: %EXE_PATH%
    echo.
    echo Please check the build output for errors
)

echo.
pause
