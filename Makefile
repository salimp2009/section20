.PHONY: clean All

All:
	@echo "----------Building project:[ SIMD_Vector_Matrix_Multiplication - Debug ]----------"
	@cd "SIMD_Vector_Matrix_Multiplication" && "$(MAKE)" -f  "SIMD_Vector_Matrix_Multiplication.mk"
clean:
	@echo "----------Cleaning project:[ SIMD_Vector_Matrix_Multiplication - Debug ]----------"
	@cd "SIMD_Vector_Matrix_Multiplication" && "$(MAKE)" -f  "SIMD_Vector_Matrix_Multiplication.mk" clean
