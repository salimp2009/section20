.PHONY: clean All

All:
	@echo "----------Building project:[ STL_Algorithms - Debug ]----------"
	@cd "STL_Algorithms" && "$(MAKE)" -f  "STL_Algorithms.mk"
clean:
	@echo "----------Cleaning project:[ STL_Algorithms - Debug ]----------"
	@cd "STL_Algorithms" && "$(MAKE)" -f  "STL_Algorithms.mk" clean
