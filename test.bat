@ECHO OFF

cmake --build build

:: cd build\tests
:: ctest
:: cd ..\..

cd build\tests\game
ctest
cd ..\..\..

cd build\tests\editor
ctest
cd ..\..\..