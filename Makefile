.PHONY: clean All

All:
	@echo "----------Building project:[ Future_Promise_Synchronise - Debug ]----------"
	@cd "Future_Promise_Synchronise" && "$(MAKE)" -f  "Future_Promise_Synchronise.mk"
clean:
	@echo "----------Cleaning project:[ Future_Promise_Synchronise - Debug ]----------"
	@cd "Future_Promise_Synchronise" && "$(MAKE)" -f  "Future_Promise_Synchronise.mk" clean
