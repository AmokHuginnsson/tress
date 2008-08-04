.PHONY: test-env

.DEFAULT:
	$(MAKE) -f Makefile $(<)

all: test-env Makefile
	$(MAKE) -f Makefile all

Makefile: configure
	./configure

configure: configure.ac
	autoconf

-include local.mk
