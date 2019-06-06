@echo off
rem enables the use of !, ! makes so var can be expanded dynamically
setlocal EnableDelayedExpansion 

if "%1" == "compile" goto COMPILE
if "%1" == "makeInclude" goto MAKEINCLUDE
if "%1" == "delInclude" goto DELINCLUDE
if "%1" == "help" goto HELP
goto EOF

:COMPILE
rem  Need to send every .cpp file to compiler. So I make a src variable and fill it with all .cpp files that are in src folder
set src=
for %%f in (src\*.cpp) do set src=!src! %%f

rem Using -I to include all header files in incude folder for compilation. Also add src variable at the end to distinguish these files as mine
set myFiles=-I.\include %src%

rem Linking sfml libraries to compilator
set sfml=-I.\SFML\include -L.\SFML\lib -l:libsfml-graphics.a -l:libsfml-window.a -l:libsfml-system.a

if "%2" == "" g++ -static-libgcc main.cpp -o BattleShipsW.exe -std=c++14 %myFiles% %sfml%

if "%2" == "run" g++ -static-libgcc main.cpp  -o BattleShipsW.exe -std=c++14 %myFiles% %sfml% && BattleShipsW.exe

goto EOF

:MAKEINCLUDE
if "%2" == "" goto EOF

type nul > include\%2.h
type nul > src\%2.cpp
notepad++ include\%2.h src\%2.cpp

goto EOF

:DELINCLUDE

del include\%2.h
del src\%2.cpp

goto EOF

:HELP
echo compile or compile run
echo makeInclude name
echo delInclude name

goto EOF

:EOF