@echo off
rem enables the use of !, ! makes so var can be expanded dynamically
setlocal EnableDelayedExpansion 

rem  Need to send every .cpp file to compiler. So I make a src variable and fill it with all .cpp files that are in src folder
set src=
for %%f in (src\*.cpp) do set src=!src! %%f

rem Using -I to include all header files in incude folder for compilation. Also add src variable at the end to distinguish these files as mine
set myFiles=-Iinclude %src%
echo %src%
rem Linking sfml libraries to compilator
set sfml=-LSFML/lib -l:libsfml-system.a -l:libsfml-window.a -l:libsfml-graphics.a

g++ main.cpp  -o BattleShips.exe -std=c++14 %myFiles% %sfml%

if "%1" == "run" BattleShips.exe