CC      := gcc
CFLAGS  := -g -Wall
LDFLAGS :=
OBJS    := main.o

# main longest common subsequence program (lcs)
lcs: $(OBJS)
	$(CC) $(LDFLAGS) -o lcs $(OBJS)

# Make c files into o files automaticaaly
.c.o:
	$(CC) -c $(CFLAGS) $<

# all/clean phonies
.PHONY: all clean

all: lcs

clean:
	rm -rf lcs *.o
