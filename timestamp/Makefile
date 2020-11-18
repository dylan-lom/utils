timestamp.deb: bin/timestamp
	cp bin/timestamp dist/usr/bin/
	dpkg-deb -b dist
	mv dist.deb dist/timestamp.deb

install: timestamp.deb
	dpkg -i dist/timestamp.deb

clean:
	rm dist/timestamp.deb dist/usr/bin/timestamp
