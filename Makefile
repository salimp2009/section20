.PHONY: clean All

All:
	@echo "----------Building project:[ SIMD_DotArrays_sse - Debug ]----------"
	@cd "SIMD_DotArrays_sse" && "$(MAKE)" -f  "SIMD_DotArrays_sse.mk"
clean:
	@echo "----------Cleaning project:[ SIMD_DotArrays_sse - Debug ]----------"
	@cd "SIMD_DotArrays_sse" && "$(MAKE)" -f  "SIMD_DotArrays_sse.mk" clean
