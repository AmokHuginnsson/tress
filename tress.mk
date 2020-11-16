#$(eval DIR_ROOT?=$(subst /Makefile.mk.in,,$(lastword $(realpath $(foreach DIR,$(subst /, ,$(CURDIR)), $(eval DIR_ROOT_TEST=$(DIR_ROOT_TEST)/$(DIR))$(DIR_ROOT_TEST)/Makefile.mk.in)))))

.PHONY: test memcheck

test: $(TARGET)
	@cd $(if $(DIR_ROOT),$(DIR_ROOT),.) && mkdir -p out/glob/1 out/glob/3 && sqlite3 out/tress.sqlite < data/sqlite.sql && \
	chmod 600 ./data/karatsuba.bc && \
	chmod -R +rwX ./out/glob && \
	mkdir -p ./out/glob/2 && \
	touch ./out/glob/1/abc ./out/glob/2/abd ./out/glob/3/abe && \
	chmod 100 ./out/glob/2 && \
	PROC_LIMIT=1024 . _aux/set-limits.sh && \
	env -i $(TRESS_ENV) \
		PATH="${PATH}" \
		LD_LIBRARY_PATH="${LD_LIBRARY_PATH}" \
		LC_CTYPE="${LC_CTYPE}" \
		LC_COLLATE="${LC_COLLATE}" \
		TZ="Europe/Warsaw" \
		TRESSRC="tressrc" \
		YAAL_LOG_LEVEL="info" \
		DEFAULT_TARGET="debug" \
		TRESS_CLOCK_QUALITY_MULTIPLIER="$${TRESS_CLOCK_QUALITY_MULTIPLIER:-1}" \
	./build/$(if $(TARGET),$(TARGET),debug)/tress/1exec -q $(TRESS_ARG) < /dev/null > /dev/null

memcheck: $(TARGET)
	@cd $(if $(DIR_ROOT),$(DIR_ROOT),.) && mkdir -p out && sqlite3 out/tress.sqlite < data/sqlite.sql && \
	. _aux/set-limits.sh && $(TRESS_ENV) valgrind --gen-suppressions=all ./build/$(if $(TARGET),$(TARGET),debug)/tress/1exec -q $(TRESS_ARG) < /dev/null > /dev/null; \
	test $$? -ne 255

