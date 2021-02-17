VERSION = v0.0.1
SRCDIR  = src
DISTDIR = dist
DISTBIN = $(DISTDIR)/usr/bin
DISTMAN = $(DISTDIR)/usr/share/man

all: djl-utils.deb

dist: bin DEBIAN.control
bin: line sign pasta suptime countdown truthy stopwatch timestamp

distdir:
	mkdir -p $(DISTBIN)
	mkdir -p $(DISTMAN)/man1

line: $(SRCDIR)/line.c $(SRCDIR)/line.1 distdir
	cc -o $(DISTBIN)/line $(SRCDIR)/line.c
	cp $(SRCDIR)/line.1 $(DISTMAN)/man1/line.1

sign: $(SRCDIR)/sign $(SRCDIR)/sign.1 distdir
	cp $(SRCDIR)/sign $(DISTBIN)/sign
	cp $(SRCDIR)/sign.1 $(DISTMAN)/man1/sign.1

pasta: $(SRCDIR)/pasta distdir
	cp $(SRCDIR)/pasta $(DISTBIN)/pasta

truthy: $(SRCDIR)/truthy.c distdir
	cc -o $(DISTBIN)/truthy $(SRCDIR)/truthy.c

suptime: $(SRCDIR)/suptime.c $(SRCDIR)/suptime.1 distdir
	cc -o $(DISTBIN)/suptime $(SRCDIR)/suptime.c
	cp $(SRCDIR)/suptime.1 $(DISTMAN)/man1/suptime.1

countdown: $(SRCDIR)/countdown.c $(SRCDIR)/countdown.1 distdir
	cc -o $(DISTBIN)/countdown $(SRCDIR)/countdown.c
	cp $(SRCDIR)/countdown.1 $(DISTMAN)/man1/countdown.1

stopwatch: $(SRCDIR)/stopwatch.c $(SRCDIR)/stopwatch.1 distdir
	cc -o $(DISTBIN)/stopwatch $(SRCDIR)/stopwatch.c
	cp $(SRCDIR)/stopwatch.1 $(DISTMAN)/man1/stopwatch.1

timestamp: $(SRCDIR)/timestamp $(SRCDIR)/timestamp.1 distdir
	cp $(SRCDIR)/timestamp $(DISTBIN)
	cp $(SRCDIR)/timestamp.1 $(DISTMAN)/man1/timestamp.1


DEBIAN.control: $(SRCDIR)/DEBIAN/control distdir
	rm -rf dist/DEBIAN
	cp -r $(SRCDIR)/DEBIAN dist/DEBIAN

djl-utils.deb: dist
	dpkg-deb -b dist
	mv dist.deb dist/djl-utils.deb

install: djl-utils.deb
	dpkg -i dist/djl-utils.deb

tarball:
	tar -czf $(VERSION).tgz LICENSE Makefile src/

clean:
	rm -rf dist
