@echo off

if not exist bin (
	echo ./bin folder not found!
	goto :error
)
	
if not exist prj\x64\Release\SDL2ImGui.exe (
	echo prj\x64\Release\SDL2ImGui.exe not found!
	goto :error
)

if not "%1"=="min" start /min cmd /c %0 min & Exit /b
xcopy prj\x64\Release bin /s /q /y

cd bin
SDL2ImGui.exe

:error
pause