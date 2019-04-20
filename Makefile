.PHONY: clean All

All:
	@echo "----------Building project:[ Thread_Call_Once_Flag - Debug ]----------"
	@cd "Thread_Call_Once_Flag" && "$(MAKE)" -f  "Thread_Call_Once_Flag.mk"
clean:
	@echo "----------Cleaning project:[ Thread_Call_Once_Flag - Debug ]----------"
	@cd "Thread_Call_Once_Flag" && "$(MAKE)" -f  "Thread_Call_Once_Flag.mk" clean
