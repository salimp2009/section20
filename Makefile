.PHONY: clean All

All:
	@echo "----------Building project:[ Templates_Compile_Time_If - Release ]----------"
	@cd "Templates_Compile_Time_If" && "$(MAKE)" -f  "Templates_Compile_Time_If.mk"
clean:
	@echo "----------Cleaning project:[ Templates_Compile_Time_If - Release ]----------"
	@cd "Templates_Compile_Time_If" && "$(MAKE)" -f  "Templates_Compile_Time_If.mk" clean
