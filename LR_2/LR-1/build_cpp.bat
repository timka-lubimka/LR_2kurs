@echo off
cd /d "%~dp0"
g++ -std=c++17 -Wall -Wextra -pedantic -I cpp cpp/main.cpp cpp/registry.cpp cpp/array.cpp cpp/singly_list.cpp cpp/doubly_list.cpp cpp/stack.cpp cpp/queue.cpp cpp/complete_tree.cpp cpp/storage.cpp cpp/commands.cpp -o lab1.exe
if errorlevel 1 exit /b 1
echo Build complete: lab1.exe
