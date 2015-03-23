###########################
# Fichier Makefile        #
# Benjamin Debotté - 2015 #
###########################
PROJECT=Graph

ROOT_PATH=.

LDFLAGS+=

CFLAGS=-c -DTESTING -g -Wall -ansi -pedantic

CC=gcc
SRCS=$(notdir $(wildcard $(ROOT_PATH)/*.c))
BINARY=${PROJECT}

# Liste des fichiers objets
OBJECTS=$(SRCS:%.c=%.o)

all: $(BINARY)

$(BINARY):  $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(PROJECT)

.c.o:
	$(CC) $(INCFLAGS) $(CFLAGS) -fPIC $< -o $@

clean:
	rm -f *.o
	rm -f ${PROJECT}

