# Anti-compiler stuff (Forbidden compilation test framework (FCTF))
ACXX = $(DIR_ROOT)/FCTF/acxx
ASS = acxx
AOS = ao
ADS = ad
ASRCS = $(strip $(sort $(shell cd $(DIR_ROOT)/ && $(FIND) ./must_not_compile -name "*.$(ASS)")))
AOBJS = $(patsubst %.$(ASS),%.$(AOS),$(ASRCS))
DIRS += $(DIR_BUILD)/must_not_compile

%.$(AOS): %.$(ASS)
	@$(eval $(call IDENT_HELPER,$(<))) $(call msg,printf "%b" "$($(CURR_PROGRESS_INDICATOR))$(eval $(call PROGRESS_INDICATOR))Anti-Compiling \`$(subst $(DIR_ROOT)/,,$(<))' ... " && ) \
	mkdir -p $(DIR_BUILD)/must_not_compile ; \
	/bin/rm -f "$(@)" && \
	$(call invoke,$(DXX) $(CXXFLAGS) -xc++ -DMAKE_DEP -MM $(<) -MT $(@) -MT $(@:.$(OS)=.$(DS)) -MF $(@:.$(OS)=.$(DS))) && \
	$(call invoke,$(ACXX) $(CXXFLAGS) $(<) -c -o $(@) 2>&1 | tee -a make.log) && \
	test -f $(@) \
	$(call msg,&& printf "%b$(NL)" "done.$(CL)")

EXTRA_DEPS_TARGET_tress=$(AOBJS)
