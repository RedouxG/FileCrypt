@echo off
REM ----------------------------------------
REM BUILD CMAKE FOR WINDOWS
REM ----------------------------------------
@echo on

cmake -G "MinGW Makefiles" -B./build/CMake -S.
