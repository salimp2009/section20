.PHONY: clean All

All:
	@echo "----------Building project:[ Classes_Basics_01 - Debug ]----------"
	@cd "Classes_Basics_01" && "$(MAKE)" -f  "Classes_Basics_01.mk"
clean:
	@echo "----------Cleaning project:[ Classes_Basics_01 - Debug ]----------"
	@cd "Classes_Basics_01" && "$(MAKE)" -f  "Classes_Basics_01.mk" clean
