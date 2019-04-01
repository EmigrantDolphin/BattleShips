#!/bin/bash

if [[ "$1" == "compile" ]]
then

	#sfml libraries
	sfml="-lsfml-graphics -lsfml-window -lsfml-system"

	#my src files
	mysrc="-Iinclude"
	for f in src/*.cpp
	do
		mysrc+=" $f"
	done

	if [[ "$2" == "" ]]
	then
		g++ main.cpp -o BattleShipsL.asd $sfml $mysrc
	fi	

	if [[ "$2" == "run" ]]
	then
		g++ main.cpp -o BattleShipsL.out $sfml $mysrc && ./BattleShipsL.out
	fi
fi

if [[ "$1" == "makeInclude" ]]
then
	if [[ "$2" != "" ]]
	then
		touch src/$2.cpp
		touch include/$2.h
	fi
fi

if [[ "$1" == "delInclude" ]]
then
	rm src/$2.cpp
	rm include/$2.h
fi

if [[ "$1" == "help" ]]
then
	echo "compile or compile run"
	echo "makeInclude name"
	echo "delInclude name"
fi
		


