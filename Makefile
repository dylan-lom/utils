.PHONY: all clean

all: confirm line stopwatch suptime timestamp truthy

clean:
	rm -f confirm line stopwatch suptime timestamp truthy

CFLAGS=-Wall -Wextra -pedantic
confirm: confirm.c
	cc $(CFLAGS) -o confirm confirm.c

line: line.c
	cc $(CFLAGS) -o line line.c

stopwatch: stopwatch.c
	cc $(CFLAGS) -o stopwatch stopwatch.c

suptime: suptime.c
	cc $(CFLAGS) -o suptime suptime.c

timestamp: timestamp.c
	cc $(CFLAGS) -o timestamp timestamp.c

truthy: truthy.c
	cc $(CFLAGS) -o truthy truthy.c

