#!/bin/bash

echo "Hit [1] to compile, hit [2] to build"
read num
case $num in
	[1])
		g++ -c Sorting.cpp
		;;
	[2])
		g++ Sorting.o -o Sorting -lsfml-graphics -lsfml-window -lsfml-system
		;;
	*)
		echo "Invalid"
		;;
esac
echo "Done"
