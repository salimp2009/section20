.PHONY: clean All

All:
	@echo "----------Building project:[ test01 - Debug ]----------"
	@cd "test01" && "$(MAKE)" -f  "test01.mk"
clean:
	@echo "----------Cleaning project:[ test01 - Debug ]----------"
	@cd "test01" && "$(MAKE)" -f  "test01.mk" clean
