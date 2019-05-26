.PHONY: clean All

All:
	@echo "----------Building project:[ Allocator_Stack_Allocator_MemoryPool - Debug ]----------"
	@cd "Allocator_Stack_Allocator_MemoryPool" && "$(MAKE)" -f  "Allocator_Stack_Allocator_MemoryPool.mk"
clean:
	@echo "----------Cleaning project:[ Allocator_Stack_Allocator_MemoryPool - Debug ]----------"
	@cd "Allocator_Stack_Allocator_MemoryPool" && "$(MAKE)" -f  "Allocator_Stack_Allocator_MemoryPool.mk" clean
