.PHONY: clean All

All:
	@echo "----------Building project:[ lambda_basics - Debug ]----------"
	@cd "lambda_basics" && "$(MAKE)" -f  "lambda_basics.mk"
clean:
	@echo "----------Cleaning project:[ lambda_basics - Debug ]----------"
	@cd "lambda_basics" && "$(MAKE)" -f  "lambda_basics.mk" clean
