.PHONY: clean All

All:
	@echo "----------Building project:[ Future_DotProduct_Async - Debug ]----------"
	@cd "Future_DotProduct_Async" && "$(MAKE)" -f  "Future_DotProduct_Async.mk"
clean:
	@echo "----------Cleaning project:[ Future_DotProduct_Async - Debug ]----------"
	@cd "Future_DotProduct_Async" && "$(MAKE)" -f  "Future_DotProduct_Async.mk" clean
