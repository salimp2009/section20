.PHONY: clean All

All:
	@echo "----------Building project:[ Thread_Safe_Stack - Debug ]----------"
	@cd "Thread_Safe_Stack" && "$(MAKE)" -f  "Thread_Safe_Stack.mk"
clean:
	@echo "----------Cleaning project:[ Thread_Safe_Stack - Debug ]----------"
	@cd "Thread_Safe_Stack" && "$(MAKE)" -f  "Thread_Safe_Stack.mk" clean
