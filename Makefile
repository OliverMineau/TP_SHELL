SRCDIR=./src
OBJDIR=./temp
INCLUDEDIR=./includes
EXEC=shell
TESTDIR=./tests
DOXDIR=./doxygen

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

ifndef DEBUG
	DEBUG=0
endif

ifndef TEST
	TEST=test12.txt
endif

.PHONY: all, clean, init, testAll, test

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

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -c -o $@ $<

$(EXEC):$(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)


test:
	./sdriver.pl -t $(TESTDIR)/$(TEST) -s ./shell

testAll:
	for num in $(TESTDIR)/*; do\
		./sdriver.pl -t $$num -s ./shell;\
		echo;\
	done

init:
	mkdir -p temp

doxy:
	doxygen $(DOXDIR)/doxy-convert.conf
	cd $(DOXDIR)/latex;make;cp refman.pdf ../MINI_SHELL_DOC_MINEAU_THACH.pdf;

clean:
	rm -f $(EXEC) $(OBJDIR)/*

