.PHONY: clean All

All:
	@echo "----------Building project:[ Thread_Safe_Initiliaze - Debug ]----------"
	@cd "Thread_Safe_Initiliaze" && "$(MAKE)" -f  "Thread_Safe_Initiliaze.mk"
clean:
	@echo "----------Cleaning project:[ Thread_Safe_Initiliaze - Debug ]----------"
	@cd "Thread_Safe_Initiliaze" && "$(MAKE)" -f  "Thread_Safe_Initiliaze.mk" clean
