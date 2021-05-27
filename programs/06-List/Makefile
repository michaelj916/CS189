# makefile for Recursion program 6

PROG = maze
CC = g++
CPPFLAGS = -g -Wall
OBJS = main.o Maze.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : 
	$(CC) $(CPPFLAGS) -c main.cpp

Maze.o : Maze.h
	$(CC) $(CPPFLAGS) -c Maze.cpp

clean:
	rm -f core $(PROG) $(OBJS) 
