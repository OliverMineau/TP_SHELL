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

ifndef T
	TEST=exit.txt
else
	TEST=$(T).txt
	EXEC=test
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

#Test seul, make test=02 pour tester le fichier test02.txt 
test:
	./sdriver.pl -v -t $(TESTDIR)/$(TEST) -s ./shell

#Test tous les fichiers tests
testAll:
	for num in $(TESTDIR)/*; do\
		./sdriver.pl -t $$num -s ./shell;\
		echo;\
	done

#Creation du dossier vide contenant les fichiers temporaires.
init:
	mkdir -p temp

#Creation de la documentation et copie du pdf
doxy:
	doxygen $(DOXDIR)/doxy-convert.conf
	cd $(DOXDIR)/latex;make;cp refman.pdf ../MINI_SHELL_DOC_MINEAU_THACH.pdf;

clean:
	rm -f $(EXEC) $(OBJDIR)/*

