.PHONY: install clean

all: install

install:
	$(MAKE) -C build install

clean:
	rm -rf build
