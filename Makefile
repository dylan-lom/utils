all: djl-utils.deb

dist: sign pasta suptime timestamp

sign: src/sign
	cp src/sign dist/usr/bin

pasta: src/pasta
	cp src/pasta dist/usr/bin

suptime: src/suptime.c
	cc -o dist/usr/bin/suptime src/suptime.c

timestamp: src/timestamp
	cp src/timestamp dist/usr/bin

djl-utils.deb: dist
	dpkg-deb -b dist
	mv dist.deb dist/djl-utils.deb

install: djl-utils.deb
	dpkg -i dist/djl-utils.deb

clean:
	rm -f dist/usr/bin/* dist/djl-utils.deb
