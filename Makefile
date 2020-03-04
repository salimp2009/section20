.PHONY: clean All

All:
	@echo "----------Building project:[ Weak_Ptr_2 - Debug ]----------"
	@cd "Weak_Ptr_2" && "$(MAKE)" -f  "Weak_Ptr_2.mk"
clean:
	@echo "----------Cleaning project:[ Weak_Ptr_2 - Debug ]----------"
	@cd "Weak_Ptr_2" && "$(MAKE)" -f  "Weak_Ptr_2.mk" clean
