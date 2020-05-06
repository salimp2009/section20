.PHONY: clean All

All:
	@echo "----------Building project:[ Allocator_Polymorphic_Memory_Resource - Debug ]----------"
	@cd "Allocator_Polymorphic_Memory_Resource" && "$(MAKE)" -f  "Allocator_Polymorphic_Memory_Resource.mk"
clean:
	@echo "----------Cleaning project:[ Allocator_Polymorphic_Memory_Resource - Debug ]----------"
	@cd "Allocator_Polymorphic_Memory_Resource" && "$(MAKE)" -f  "Allocator_Polymorphic_Memory_Resource.mk" clean
