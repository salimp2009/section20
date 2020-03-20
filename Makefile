.PHONY: clean All

All:
	@echo "----------Building project:[ Meta_Programming_forNArgs - Debug ]----------"
	@cd "Meta_Programming_forNArgs" && "$(MAKE)" -f  "Meta_Programming_forNArgs.mk"
clean:
	@echo "----------Cleaning project:[ Meta_Programming_forNArgs - Debug ]----------"
	@cd "Meta_Programming_forNArgs" && "$(MAKE)" -f  "Meta_Programming_forNArgs.mk" clean
