.PHONY: clean All

All:
	@echo "----------Building project:[ Future_Defered_Async - Debug ]----------"
	@cd "Future_Defered_Async" && "$(MAKE)" -f  "Future_Defered_Async.mk"
clean:
	@echo "----------Cleaning project:[ Future_Defered_Async - Debug ]----------"
	@cd "Future_Defered_Async" && "$(MAKE)" -f  "Future_Defered_Async.mk" clean
