CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ1 = main.o effects.o TurtleGraphics.o linked_list.o utility.o output.o
OBJ2 = main.o effects.o TurtleGraphicsSimple.o linked_list.o utility.o output.o
OBJ3 = main.o effects.o TurtleGraphicsDebug.o linked_list.o utility.o output.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple
EXEC3 = TurtleGraphicsDebug

all : $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -o $(EXEC1) -lm

$(EXEC2) : $(OBJ2)
	$(CC) $(OBJ2) -o $(EXEC2) -lm

$(EXEC3) : $(OBJ3)
	$(CC) $(OBJ3) -o $(EXEC3) -lm

main.o : main.c linked_list.h 
	$(CC) -c main.c $(CFLAGS)

TurtleGraphics.o : TurtleGraphics.c effects.h TurtleGraphics.h linked_list.h utility.h log.h output.h
	$(CC) -c TurtleGraphics.c $(CFLAGS)

TurtleGraphicsSimple.o : TurtleGraphics.c effects.h TurtleGraphics.h linked_list.h utility.h log.h output.h
	$(CC) -c TurtleGraphics.c $(CFLAGS) -D SIMPLE -o TurtleGraphicsSimple.o

TurtleGraphicsDebug.o : TurtleGraphics.c effects.h TurtleGraphics.h linked_list.h utility.h log.h output.h
	$(CC) -c TurtleGraphics.c $(CFLAGS) -D DEBUG -o TurtleGraphicsDebug.o

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

utility.o : utility.c utility.h 
	$(CC) -c utility.c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
	$(CC) -c linked_list.c $(CFLAGS)

output.o : output.c output.h 
	$(CC) -c output.c $(CFLAGS)

clean : 
	rm -f $(EXEC1) $(EXEC2) $(EXEC3) $(OBJ1) $(OBJ2) $(OBJ3)
