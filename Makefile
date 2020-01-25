.PHONY: clean All

All:
	@echo "----------Building project:[ STL_Containers - Debug ]----------"
	@cd "STL_Containers" && "$(MAKE)" -f  "STL_Containers.mk"
clean:
	@echo "----------Cleaning project:[ STL_Containers - Debug ]----------"
	@cd "STL_Containers" && "$(MAKE)" -f  "STL_Containers.mk" clean
