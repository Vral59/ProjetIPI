# Varible

CC=gcc
CFLAGS = -Wall -Wextra
EXEC = projet

all: $(EXEC)

# Compilation finale
projet: main.o pile.o
	$(CC) $(CFLAGS) -g -o projet main.o pile.o

# Compilation de pile.o
pile.o: pile.c pile.h
	$(CC) $(CFLAGS) -c pile.c

# Compilation de main.o
main.o: main.c pile.h
	$(CC) $(CFLAGS) -c main.c


#Clean des fichier temp
clean:
	rm -rf *.o
