.PHONY: all test install clean

all:
	$(MAKE) -C build all

test:
	$(MAKE) -C build test

install:
	$(MAKE) -C build install

clean:
	rm -rf build
