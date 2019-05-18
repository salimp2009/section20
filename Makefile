.PHONY: clean All

All:
	@echo "----------Building project:[ Variadic_Templates_BinaryTree_Traverse - Debug ]----------"
	@cd "Variadic_Templates_BinaryTree_Traverse" && "$(MAKE)" -f  "Variadic_Templates_BinaryTree_Traverse.mk"
clean:
	@echo "----------Cleaning project:[ Variadic_Templates_BinaryTree_Traverse - Debug ]----------"
	@cd "Variadic_Templates_BinaryTree_Traverse" && "$(MAKE)" -f  "Variadic_Templates_BinaryTree_Traverse.mk" clean
