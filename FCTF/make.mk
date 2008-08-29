# Anti-compiler stuff (Forbidden compilation test framework (FCTF))
ACXX = $(DIR_ROOT)/FCTF/acxx
ASS = acxx
AOS = ao
ADS = ad
ASRCS = $(strip $(sort $(shell cd $(DIR_ROOT)/ && $(FIND) ./must_not_compile -name "*.$(ASS)")))
AOBJS = $(patsubst %.$(ASS),%.$(AOS),$(ASRCS))

%.$(AOS): %.$(ASS)
	@echo -n "Anti-Compiling \`$(subst $(DIR_ROOT)/,,$(<))' ... "; \
	mkdir -p $(DIR_BUILD)/must_not_compile ; \
	/bin/rm -f "$(@)"; \
	$(DXX) $(CXXFLAGS) -xc++ -DBUG_0 -MM $(<) -MT $(@) -MT $(@:.$(OS)=.$(DS)) -MF $(@:.$(OS)=.$(DS)) && \
	$(ACXX) $(CXXFLAGS) $(<) -c -o $(@) 2>&1 | tee -a make.log && \
	test -f $(@) && \
	echo $(NONL) "done.$(CL)"

OBJS += $(AOBJS)
