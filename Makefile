.PHONY: clean All

All:
	@echo "----------Building project:[ Future_PackagedTask_Reuse - Debug ]----------"
	@cd "Future_PackagedTask_Reuse" && "$(MAKE)" -f  "Future_PackagedTask_Reuse.mk"
clean:
	@echo "----------Cleaning project:[ Future_PackagedTask_Reuse - Debug ]----------"
	@cd "Future_PackagedTask_Reuse" && "$(MAKE)" -f  "Future_PackagedTask_Reuse.mk" clean
