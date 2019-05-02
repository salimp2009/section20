.PHONY: clean All

All:
	@echo "----------Building project:[ Pairs_Tuples - Debug ]----------"
	@cd "Pairs_Tuples" && "$(MAKE)" -f  "Pairs_Tuples.mk"
clean:
	@echo "----------Cleaning project:[ Pairs_Tuples - Debug ]----------"
	@cd "Pairs_Tuples" && "$(MAKE)" -f  "Pairs_Tuples.mk" clean
