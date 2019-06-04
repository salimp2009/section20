.PHONY: clean All

All:
	@echo "----------Building project:[ Type_Traits_MetaProgramming_Conditional - Debug ]----------"
	@cd "Type_Traits_MetaProgramming_Conditional" && "$(MAKE)" -f  "Type_Traits_MetaProgramming_Conditional.mk"
clean:
	@echo "----------Cleaning project:[ Type_Traits_MetaProgramming_Conditional - Debug ]----------"
	@cd "Type_Traits_MetaProgramming_Conditional" && "$(MAKE)" -f  "Type_Traits_MetaProgramming_Conditional.mk" clean
