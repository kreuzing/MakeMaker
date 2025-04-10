CC = g++

CFLAGS = -Wall

OBJECTS = main.o ProgramTree.o ProgramClass.o

MakeMaker :  $(OBJECTS)
	$(CC) $(CFLAGS) -o MakeMaker  $(OBJECTS)

main.o : main.cpp ProgramTree.h ProgramClass.h 
	$(CC) $(CFLAGS) -c main.cpp

ProgramTree.o : ProgramTree.h ProgramClass.h

ProgramClass.o : ProgramClass.h

clean :
	rm MakeMaker $(OBJECTS)