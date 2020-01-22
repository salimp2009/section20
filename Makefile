.PHONY: clean All

All:
	@echo "----------Building project:[ test4 - Debug ]----------"
	@cd "test4" && "$(MAKE)" -f  "test4.mk"
clean:
	@echo "----------Cleaning project:[ test4 - Debug ]----------"
	@cd "test4" && "$(MAKE)" -f  "test4.mk" clean
