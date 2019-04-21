.PHONY: clean All

All:
	@echo "----------Building project:[ Thread_Singleton_OnceFlag - Debug ]----------"
	@cd "Thread_Singleton_OnceFlag" && "$(MAKE)" -f  "Thread_Singleton_OnceFlag.mk"
clean:
	@echo "----------Cleaning project:[ Thread_Singleton_OnceFlag - Debug ]----------"
	@cd "Thread_Singleton_OnceFlag" && "$(MAKE)" -f  "Thread_Singleton_OnceFlag.mk" clean
