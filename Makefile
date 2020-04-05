.PHONY: clean All

All:
	@echo "----------Building project:[ Concurrency_Atomic_Signal_Fence - Debug ]----------"
	@cd "Concurrency_Atomic_Signal_Fence" && "$(MAKE)" -f  "Concurrency_Atomic_Signal_Fence.mk"
clean:
	@echo "----------Cleaning project:[ Concurrency_Atomic_Signal_Fence - Debug ]----------"
	@cd "Concurrency_Atomic_Signal_Fence" && "$(MAKE)" -f  "Concurrency_Atomic_Signal_Fence.mk" clean
