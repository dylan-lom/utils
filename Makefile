all: djl-utils.deb

timestamp: src/timestamp
	cp src/timestamp dist/usr/bin

sign: src/sign
	cp src/sign dist/usr/bin

djl-utils.deb: timestamp sign
	dpkg-deb -b dist
	mv dist.deb dist/djl-utils.deb

install: djl-utils.deb
	dpkg -i dist/djl-utils.deb

clean:
	rm -f dist/usr/bin/* dist/djl-utils
