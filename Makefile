CC = gcc
CFLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -lm -g
BDIR = ./build

HELPERS = ./log/log.c ./hashmap/hashmap.c

all:
	$(CC) ./korean.c $(HELPERS) -o $(BDIR)/korean $(CFLAGS)

clean:
	rm -f $(BDIR)/korean
