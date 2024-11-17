@echo off
if not exist bin mkdir bin

python --version 2>NUL
if not errorlevel 0 goto :dumbcopy

python make_data.py
exit /b

: dumbcopy
xcopy data bin /s /q /y