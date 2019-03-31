@echo off

if [%1] == [] goto err

set fileName=%1

del include\%fileName%.h
del src\%fileName%.cpp
goto eof

:err
echo no file name for deletion specified

:eof