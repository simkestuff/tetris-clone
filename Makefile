CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -ggdb
LDFLAGS =
LIBS =
OUTPUT = build
SRC = game.c board.c tetromino.c


vpath %.c src
vpath %.h include

default: app

.PHONY: clean

app: main.c $(SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(OUTPUT)/$@ $^

clean:
	rm -f build/*
