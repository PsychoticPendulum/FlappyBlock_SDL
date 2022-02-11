NAME=FlappyBlock
CC=gcc
CFLAGS=-Wall -std=c99
LIBS=-lm -lSDL2 -lSDL2_ttf

fml: *.c
	$(CC) src/*.c -o $(NAME) $(CFLAGS) $(LIBS) 

object: *.c
	$(CC) src/*.c -c $(FLAGS) $(LIBS)

binary: *.o
	$(CC) src/*.o -o $(NAME) $(CFLAGS) $(LIBS)

clean:
	rm -v *.o
