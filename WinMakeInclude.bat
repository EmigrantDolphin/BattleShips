@echo off

if [%1] == [] goto err

set incName=%1

type nul > include\%incName%.h
type nul > src\%incName%.cpp

notepad++ include\%incName%.h src\%incName%.cpp
goto eof

:err
echo no file name specified

:eof