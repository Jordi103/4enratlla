
all: 4enratlla

# Fitxers objecte
4enratlla.o: 4enratlla.c
	gcc -c -Wall -O2 4enratlla.c
minimax.o: minimax.c
	gcc -c -Wall -O2 minimax.c
partides.o: partides.c
	gcc -c -Wall -O2 partides.c


# Fitxers executables
4enratlla: 4enratlla.o minimax.o partides.o
	gcc -o 4enratlla 4enratlla.o minimax.o partides.o


# Neteja
clean:
	rm -f *.o
realclean:
	rm -f *.o 4enratlla partides.dat
	
