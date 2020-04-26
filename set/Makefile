# Makefile for 'set' module
#
# Sydney Friedland, April 2020
# 
# Based on Makefile for 'bags' module by:
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Temi Prioleau, January 2020

PROG = settest
OBJS = settest.o set.o
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

settest.o: set.h
set.o: set.h

.PHONY: test clean

# more information in settest.c
test: $(PROG)
	./$(PROG)

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks