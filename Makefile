.PHONY: clean All

All:
	@echo "----------Building project:[ STL_Unordered_Containers_Sets_Maps_Hashing - Debug ]----------"
	@cd "STL_Unordered_Containers_Sets_Maps_Hashing" && "$(MAKE)" -f  "STL_Unordered_Containers_Sets_Maps_Hashing.mk"
clean:
	@echo "----------Cleaning project:[ STL_Unordered_Containers_Sets_Maps_Hashing - Debug ]----------"
	@cd "STL_Unordered_Containers_Sets_Maps_Hashing" && "$(MAKE)" -f  "STL_Unordered_Containers_Sets_Maps_Hashing.mk" clean
