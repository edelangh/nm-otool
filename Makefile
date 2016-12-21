
.PHONY: libft nm otool

all: libft nm otool

libft:
	@make -C libft

nm:
	@make -C nm

otool:
	@make -C otool
