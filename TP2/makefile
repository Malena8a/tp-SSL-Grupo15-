programa: main.o scanner.o
	gcc -o programa main.o scanner.o

main.o: main.c scanner.h
	gcc -c main.c

scanner.o: scanner.c scanner.h
	gcc -c scanner.c

clean:
	rm *.o programa
