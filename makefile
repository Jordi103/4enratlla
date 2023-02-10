
all: 4enratlla

# Object files
4enratlla.o: 4enratlla.c
	gcc -c -Wall -O2 4enratlla.c
minimax.o: minimax.c
	gcc -c -Wall -O2 minimax.c


# Executable files
4enratlla: 4enratlla.o minimax.o
	gcc -o 4enratlla 4enratlla.o minimax.o


# Clean
clean:
	rm -f *.o
realclean:
	rm -f *.o 4enratlla games.dat
	
