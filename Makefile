.PHONY: clean All

All:
	@echo "----------Building project:[ Thread_Promise_Future_2 - Debug ]----------"
	@cd "Thread_Promise_Future_2" && "$(MAKE)" -f  "Thread_Promise_Future_2.mk"
clean:
	@echo "----------Cleaning project:[ Thread_Promise_Future_2 - Debug ]----------"
	@cd "Thread_Promise_Future_2" && "$(MAKE)" -f  "Thread_Promise_Future_2.mk" clean
