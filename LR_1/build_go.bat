@echo off
cd /d "%~dp0go"
go build -o lab1-go.exe .
if errorlevel 1 exit /b 1
echo Build complete: lab1-go.exe
