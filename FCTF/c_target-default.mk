.DEFAULT:
	@if [ "$(suffix $(<))" != ".$(DS)" -a "$(suffix $(<))" != ".$(ADS)" -a "$(suffix $(<))" != ".mk" ] ; then \
	echo -n "$(BOLD)$(RED)"; \
	echo "Lack of \`$(<)'." | tee -a make.log; \
	echo -n "$(RS)"; fi
