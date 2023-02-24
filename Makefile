SRCDIR=./src
OBJDIR=./temp
INCLUDEDIR=./includes
EXEC=shell

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

ifndef DEBUG
	DEBUG=0
endif

.PHONY: all, clean, init

# Disable implicit rules
.SUFFIXES:

CC=gcc
CFLAGS=-Wall -g -I$(INCLUDEDIR)
VPATH=src/

# Note: -lnsl does not seem to work on Mac OS but will
# probably be necessary on Solaris for linking network-related functions 
#LIBS += -lsocket -lnsl -lrt
LIBS+=-lpthread

all: init $(EXEC)

$(OBJDIR)/shell.o: $(SRCDIR)/shell.c
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXEC):$(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)


init:
	mkdir -p temp

clean:
	rm -f $(EXEC) $(OBJDIR)/*.o 

