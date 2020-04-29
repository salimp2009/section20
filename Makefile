.PHONY: clean All

All:
	@echo "----------Building project:[ Entity_Component_System - Debug ]----------"
	@cd "Entity_Component_System" && "$(MAKE)" -f  "Entity_Component_System.mk"
clean:
	@echo "----------Cleaning project:[ Entity_Component_System - Debug ]----------"
	@cd "Entity_Component_System" && "$(MAKE)" -f  "Entity_Component_System.mk" clean
