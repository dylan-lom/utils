.PHONY: all clean

CC=gcc
BINS=confirm line suptime timestamp truthy
CFLAGS=-Wall -Wextra -pedantic -ggdb -static

all: $(BINS)

clean:
	rm -f $(BINS)

confirm: confirm.sh
	cp confirm.sh confirm
	chmod +x confirm

cuts: cuts.c
	$(CC) $(CFLAGS) -o cuts cuts.c

line: line.c
	$(CC) $(CFLAGS) -o line line.c

suptime: suptime.c
	$(CC) $(CFLAGS) -o suptime suptime.c

timestamp: timestamp.c
	$(CC) $(CFLAGS) -o timestamp timestamp.c

truthy: truthy.c
	$(CC) $(CFLAGS) -o truthy truthy.c

