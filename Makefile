.PHONY: all test install clean distclean

all:
	$(MAKE) -C build all

test:
	$(MAKE) -C build test

install:
	$(MAKE) -C build install

clean:
	$(MAKE) -C build clean

distclean:
	rm -rf build
