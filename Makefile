all: djl-utils.deb

dist: bin DEBIAN.control
bin: line sign pasta suptime countdown stopwatch timestamp

distdir:
	mkdir -p dist/usr/bin

line: src/line.c distdir
	cc -o dist/usr/bin/line src/line.c

sign: src/sign distdir
	cp src/sign dist/usr/bin

pasta: src/pasta distdir
	cp src/pasta dist/usr/bin

suptime: src/suptime.c distdir
	cc -o dist/usr/bin/suptime src/suptime.c

countdown: src/countdown.c distdir
	cc -o dist/usr/bin/countdown src/countdown.c

stopwatch: src/stopwatch.c distdir
	cc -o dist/usr/bin/stopwatch src/stopwatch.c

timestamp: src/timestamp distdir
	cp src/timestamp dist/usr/bin

DEBIAN.control: src/DEBIAN/control distdir
	rm -rf dist/DEBIAN
	cp -r src/DEBIAN dist/DEBIAN

djl-utils.deb: dist
	dpkg-deb -b dist
	mv dist.deb dist/djl-utils.deb

install: djl-utils.deb
	dpkg -i dist/djl-utils.deb

clean:
	rm -rf dist
