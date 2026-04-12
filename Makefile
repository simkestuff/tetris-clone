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

gui: guiclient.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -L./lib -lraylib -lm -lX11

clean:
	rm -f build/*
