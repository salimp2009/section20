.PHONY: clean All

All:
	@echo "----------Building project:[ Priority_Queue - Debug ]----------"
	@cd "Priority_Queue" && "$(MAKE)" -f  "Priority_Queue.mk"
clean:
	@echo "----------Cleaning project:[ Priority_Queue - Debug ]----------"
	@cd "Priority_Queue" && "$(MAKE)" -f  "Priority_Queue.mk" clean
