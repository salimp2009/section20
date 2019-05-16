.PHONY: clean All

All:
	@echo "----------Building project:[ Template_Stack_Array_Auto - Debug ]----------"
	@cd "Template_Stack_Array_Auto" && "$(MAKE)" -f  "Template_Stack_Array_Auto.mk"
clean:
	@echo "----------Cleaning project:[ Template_Stack_Array_Auto - Debug ]----------"
	@cd "Template_Stack_Array_Auto" && "$(MAKE)" -f  "Template_Stack_Array_Auto.mk" clean
