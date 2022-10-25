TARGET=file-notify.out
.DEFAULT_GOAL := $(TARGET)

SRC=
SRC+=main.c
SRC+=inotify.c

INC=-I./

CC=gcc
DBG_OPT ?= -gdwarf-2 -g3

GLIB_CFLAGS=$(shell pkg-config --cflags glib-2.0)
GLIB_LIBS=$(shell pkg-config --libs glib-2.0)

CFLAGS=-std=gnu99
#CFLAGS+=-Werror
CFLAGS+=-Wall
#CFLAGS+=-pedantic
CFLAGS+=-O2
CFLAGS+=$(GLIB_CFLAGS)

LIBS=
LIBS+=$(GLIB_LIBS)
#LIBS+=-lpaho-mqtt3as

OBJ=$(subst .c,.o,$(SRC))

%.o:%.c
	$(CC) $(DBG_OPT) $(CFLAGS) $(INC) -c $< -o $@

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $@ $(LIBS)
	chmod +x $@

clean:
	rm -rf $(TARGET)
	rm -f *.o
