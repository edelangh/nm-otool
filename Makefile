
.PHONY: libft nm otool

all: libft nm otool

libft:
	@make -C libft

nm:
	@make -C nm
	@ln -s nm/ft_nm ft_nm

otool:
	@make -C otool
	@ln -S nm/ft_otool ft_otool
