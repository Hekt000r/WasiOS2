@echo off
setlocal enabledelayedexpansion

:: --- CONFIGURATION ---
:: Point this to where you extracted the WASI-SDK
set WASI_SDK_PATH=C:\wasi-sdk
set CC="%WASI_SDK_PATH%\bin\clang.exe"
set TARGET=wasm32-wasi
set OUTPUT=core.wasm

:: --- COMPILATION ---
echo [1/2] Compiling C source files from src/...

:: Collect all .c files in the src directory
set "SOURCES="
for %%f in (src\*.c) do (
    set "SOURCES=!SOURCES! %%f"
)

if "%SOURCES%"=="" (
    echo Error: No .c files found in src/
    pause
    exit /b
)

:: Run the compiler
%CC% --target=%TARGET% -o %OUTPUT% %SOURCES%

if %ERRORLEVEL% neq 0 (
    echo.
    echo [ERROR] Compilation failed.
    pause
    exit /b
)

echo [SUCCESS] %OUTPUT% created in root.
echo.

:: --- EXECUTION ---
echo [2/2] Booting Virtual OS with Wasmtime...
echo ---------------------------------------
wasmtime %OUTPUT%

pause