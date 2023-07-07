@ECHO OFF

python scripts\editor_version.py

cmake --build build

build\src\editor\OmnisciaEditor.exe