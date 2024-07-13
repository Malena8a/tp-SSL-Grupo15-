programa: main.o tabla.o conversion.o
	gcc -o programa main.o tabla.o conversion.o

main.o: main.c tabla.h
	gcc -c main.c

tabla.o: tabla.c tabla.h conversion.h
	gcc -c tabla.c

conversion.o: conversion.c conversion.h
	gcc -c conversion.c

clean:
	rm *.o programa
