.PHONY: clean All

All:
	@echo "----------Building project:[ STL_Sequence_Containers - Debug ]----------"
	@cd "STL_Sequence_Containers" && "$(MAKE)" -f  "STL_Sequence_Containers.mk"
clean:
	@echo "----------Cleaning project:[ STL_Sequence_Containers - Debug ]----------"
	@cd "STL_Sequence_Containers" && "$(MAKE)" -f  "STL_Sequence_Containers.mk" clean
