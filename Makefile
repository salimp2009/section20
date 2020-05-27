.PHONY: clean All

All:
	@echo "----------Building project:[ Parallel_Serial_CVS_FilePath_Reader_C17 - Debug ]----------"
	@cd "Parallel_Serial_CVS_FilePath_Reader_C17" && "$(MAKE)" -f  "Parallel_Serial_CVS_FilePath_Reader_C17.mk"
clean:
	@echo "----------Cleaning project:[ Parallel_Serial_CVS_FilePath_Reader_C17 - Debug ]----------"
	@cd "Parallel_Serial_CVS_FilePath_Reader_C17" && "$(MAKE)" -f  "Parallel_Serial_CVS_FilePath_Reader_C17.mk" clean
