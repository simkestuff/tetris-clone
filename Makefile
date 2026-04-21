CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -ggdb
LDFLAGS =
LIBS = ./lib
OUTPUT = build
#SRC = game.c board.c tetromino.c
SRC = $(notdir $(wildcard src/*.c))
OBJS = $(SRC:.c=.o)
OBJS := $(addprefix $(OUTPUT)/,$(OBJS))
LIB_NAME = $(OUTPUT)/libengine.a


vpath %.c src
vpath %.h include

default: app

.PHONY: clean

app: main.c $(SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(OUTPUT)/$@ $^

$(OUTPUT)/%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

lib: $(LIB_NAME)

gui: guiclient.c $(LIB_NAME)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -L$(LIBS) -lraylib -lm -lX11 -L$(OUTPUT) -lengine

clean:
	rm -f *.o a.out build/*
