@ECHO OFF

:: python scripts\editor_version.py
python scripts\game_version.py

cmake --build build

build\src\game\OmnisciaGame.exe