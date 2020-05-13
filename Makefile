.PHONY: clean All

All:
	@echo "----------Building project:[ Templates_Class_Templates - Debug ]----------"
	@cd "Templates_Class_Templates" && "$(MAKE)" -f  "Templates_Class_Templates.mk"
clean:
	@echo "----------Cleaning project:[ Templates_Class_Templates - Debug ]----------"
	@cd "Templates_Class_Templates" && "$(MAKE)" -f  "Templates_Class_Templates.mk" clean
