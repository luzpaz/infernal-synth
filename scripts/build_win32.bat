@echo off
setlocal
if [%1] == [] goto usage
if [%2] == [] goto usage

cd ..
if not exist build\win32 mkdir build\win32
cd build\win32
cmake -DHIIR_140_SRC_DIR="%1" -DJUCE_705_SRC_DIR="%2" ../..
if %errorlevel% neq 0 exit /b !errorlevel!

msbuild /property:Configuration=Debug infernal-synth.sln
if %errorlevel% neq 0 exit /b !errorlevel!
msbuild /property:Configuration=Release infernal-synth.sln
if %errorlevel% neq 0 exit /b !errorlevel!

cd ..\..\scripts
goto :eof

:usage
echo "Usage: %0 <path-to-hiir-src> <path-to-juce-src>"
exit /B 1
