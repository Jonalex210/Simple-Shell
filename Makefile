CC = gcc
CFLAGS = -Wall

#The executable 'simpleShellJonathanNjeunje' depends on the simpleShellJonathanNjeunje.o object file
simpleShellJonathanNjeunje: simpleShellJonathanNjeunje.o
	$(CC) $(CFLAGS) -o simpleShellJonathanNjeunje simpleShellJonathanNjeunje.o

#Build simpleShellJonathanNjeunje.o (requires simpleShellJonathanNjeunje.c)
simpleShellJonathanNjeunje.o: simpleShellJonathanNjeunje.c
	$(CC) $(CFLAGS) -c simpleShellJonathanNjeunje.c

#Clean: remove all the object files
clean:
	rm simpleShellJonathanNjeunje *.o

