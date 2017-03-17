CFLAGS = -O3 -std=c99 -Wall -Werror
LIBS = -lX11 -lXss
EXE = idled

SRC_FILES = idled.c \
            brightness.c

OBJS = $(SRC_FILES:.c=.o)

$(EXE): $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
	rm *.o

$(OBJS): Makefile

clean:
	rm -f core $(EXE) *.o

setuid:
	chown root:root $(EXE)
	chmod u+s $(EXE)

