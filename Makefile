all: djl-utils.deb

dist: bin DEBIAN.control
bin: sign pasta suptime stopwatch timestamp 

sign: src/sign
	cp src/sign dist/usr/bin

pasta: src/pasta
	cp src/pasta dist/usr/bin

suptime: src/suptime.c
	cc -o dist/usr/bin/suptime src/suptime.c

stopwatch: src/stopwatch.c
	cc -o dist/usr/bin/stopwatch src/stopwatch.c

timestamp: src/timestamp
	cp src/timestamp dist/usr/bin

DEBIAN.control: src/DEBIAN/control
	rm -rf dist/DEBIAN
	cp -r src/DEBIAN dist/DEBIAN

djl-utils.deb: dist
	dpkg-deb -b dist
	mv dist.deb dist/djl-utils.deb

install: djl-utils.deb
	dpkg -i dist/djl-utils.deb

clean:
	rm -rf dist
