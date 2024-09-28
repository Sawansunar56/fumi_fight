@echo off

pushd res
devenv /debugexe ..\build\main.exe
popd
