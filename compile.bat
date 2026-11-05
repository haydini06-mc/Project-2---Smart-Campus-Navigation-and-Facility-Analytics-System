@echo off
g++ -std=c++11 -Wall -Wextra -Iinclude src\*.cpp -o campus.exe
if %errorlevel% neq 0 (
    echo Build failed.
) else (
    echo Build succeeded. Run campus.exe
)