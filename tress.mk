#$(eval DIR_ROOT?=$(subst /Makefile.mk.in,,$(lastword $(realpath $(foreach DIR,$(subst /, ,$(CURDIR)), $(eval DIR_ROOT_TEST=$(DIR_ROOT_TEST)/$(DIR))$(DIR_ROOT_TEST)/Makefile.mk.in)))))

.PHONY: test memcheck

test: debug
	@cd $(DIR_ROOT) && mkdir -p out && sqlite3 out/tress.sqlite < data/sqlite.sql && \
	. _aux/set-limits.sh && $(TRESS_ENV) ./build/debug/tress/1exec $(TRESS_ARG) > /dev/null

memcheck: debug
	@cd $(DIR_ROOT) && mkdir -p out && sqlite3 out/tress.sqlite < data/sqlite.sql && \
	. _aux/set-limits.sh && $(TRESS_ENV) valgrind ./build/debug/tress/1exec $(TRESS_ARG) > /dev/null; \
	test $$? -ne 255

