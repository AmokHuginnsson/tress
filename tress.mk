#$(eval DIR_ROOT?=$(subst /Makefile.mk.in,,$(lastword $(realpath $(foreach DIR,$(subst /, ,$(CURDIR)), $(eval DIR_ROOT_TEST=$(DIR_ROOT_TEST)/$(DIR))$(DIR_ROOT_TEST)/Makefile.mk.in)))))

.PHONY: test memcheck

test: $(TARGET)
	@cd $(if $(DIR_ROOT),$(DIR_ROOT),.) && mkdir -p out && sqlite3 out/tress.sqlite < data/sqlite.sql && \
	chmod 600 ./data/karatsuba.bc && \
	PROC_LIMIT=1024 . _aux/set-limits.sh && \
	$(TRESS_ENV) TZ="Europe/Warsaw" TRESSRC="tressrc" YAAL_LOG_LEVEL="info" DEFAULT_TARGET="debug" \
	./build/$(if $(TARGET),$(TARGET),debug)/tress/1exec -q $(TRESS_ARG)

memcheck: $(TARGET)
	@cd $(if $(DIR_ROOT),$(DIR_ROOT),.) && mkdir -p out && sqlite3 out/tress.sqlite < data/sqlite.sql && \
	. _aux/set-limits.sh && $(TRESS_ENV) valgrind --gen-suppressions=all ./build/$(if $(TARGET),$(TARGET),debug)/tress/1exec -q $(TRESS_ARG); \
	test $$? -ne 255

