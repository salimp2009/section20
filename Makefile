.PHONY: clean All

All:
	@echo "----------Building project:[ Input_Output_01 - Debug ]----------"
	@cd "Input_Output_01" && "$(MAKE)" -f  "Input_Output_01.mk"
clean:
	@echo "----------Cleaning project:[ Input_Output_01 - Debug ]----------"
	@cd "Input_Output_01" && "$(MAKE)" -f  "Input_Output_01.mk" clean
