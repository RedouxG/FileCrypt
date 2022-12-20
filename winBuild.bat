@echo off
REM ----------------------------------------
REM BUILD BATCH FOR WINDOWS
REM ----------------------------------------

REM ----------------------------------------
REM VARIABLES
REM ----------------------------------------

for /f "delims=" %%a in ('dir /s/b "*.cpp"') do call set "SRC=%%SRC%%%%a "
set destination="build/winOut.exe"

REM ----------------------------------------
REM BUILD
REM ----------------------------------------
if not exist "build" mkdir "build"
if not exist "build/Data/Common-Credentials" xcopy "src/Dependencies/Common-Credentials" "build/Data/Common-Credentials" /E /y /q /i

@echo on

g++ -W -Wextra -g3 -o %destination% %SRC%


