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
@echo on

g++ -W -o %destination% %SRC%


