@echo off
xcopy prj\x64\Release bin /s /q /y

cd bin
SDL2ImGui.exe