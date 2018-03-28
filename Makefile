.PHONY: all check install clean distclean

all:
	$(MAKE) -C build all

check:
	$(MAKE) -C build check

install:
	$(MAKE) -C build install

clean:
	$(MAKE) -C build clean

distclean:
	rm -rf build
