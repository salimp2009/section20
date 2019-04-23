.PHONY: clean All

All:
	@echo "----------Building project:[ Que - Debug ]----------"
	@cd "Que" && "$(MAKE)" -f  "Que.mk"
clean:
	@echo "----------Cleaning project:[ Que - Debug ]----------"
	@cd "Que" && "$(MAKE)" -f  "Que.mk" clean
