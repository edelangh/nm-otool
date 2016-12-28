/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:32:14 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 18:06:32 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ar.h: ARMAG, SARMAG
*/
#include "nm.h"
#include <libft.h>
#include <ft_printf.h>
#include <mach-o/ranlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <ar.h>
#define SARFMAG (sizeof(ARFMAG) - 1)

static unsigned int swap_byte(unsigned int n)
{
	n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0x00FF00FF);
	return (n << 16) | (n >> 16);
}

static int	nm_fat(const char *data)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	unsigned int		n;
	unsigned int		offset;

	fat = (struct fat_header*)data;
	n = swap_byte(fat->nfat_arch);
	arch = (struct fat_arch*)(data + sizeof(struct fat_header*));
	while (n)
	{
		if (swap_byte(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		++arch;
		--n;
	}
	return (parse_file(data + swap_byte(offset), NULL));
}

static int	nm_display_ranlib(
		struct ranlib *ran,
		const char *data, const char *file)
{
	struct ar_hdr	*ar;
	const char		*name;
	unsigned int	size;

	ar = (struct ar_hdr*)(data + ran->ran_off);
	name = ft_strstr(ar->ar_name, ARFMAG) + SARFMAG;
	size = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
	ft_dprintf(1, "\n%s(%s):\n", file, name);
	return (parse_file((char*)ar + sizeof(struct ar_hdr) + size, file));
}

void	del_ran(void *content, size_t size)
{
	(void)size;
	free(content);
}

static void *g_data = NULL;

int 	cmp_rans(struct ranlib *a, struct ranlib *b)
{
	struct ar_hdr *arch_a;
	struct ar_hdr *arch_b;

	arch_a = g_data + a->ran_off;
	arch_b = g_data + b->ran_off;
	return (ft_strcmp(arch_a->ar_name, arch_b->ar_name));
}

static int	nm_archive(const char *data, const char *file)
{
	struct ar_hdr		*ar;
	struct ranlib		*rans;
	unsigned int		size;
	unsigned int		count;
	unsigned int		i;

	t_list				*rans_lst = NULL;
	i = 0;
	ar = (struct ar_hdr*)(data + SARMAG);
	size = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
	count = *((unsigned int*)(data + sizeof(struct ar_hdr) + SARMAG + size));
	rans = (struct ranlib*)(data + sizeof(struct ar_hdr) + SARMAG + size
								+ sizeof(unsigned int));
	count /= sizeof(struct ranlib);
	while (i < count)
	{
		ft_lstpush(&rans_lst, ft_lstnew(rans + i, sizeof(struct ranlib)));
		++i;
	}
	g_data = (char*)data;
	ft_lstclean(&rans_lst, (void*)&cmp_rans, &del_ran);
	while (rans_lst)
	{
		if (nm_display_ranlib(rans_lst->content, data, file) != 0)
			return (1);
		rans_lst = rans_lst->next;
	}
	return (0);
}

int			parse_file(const char *data, const char *file)
{
	unsigned int	magic_nbr;

	magic_nbr = *(int*)data;
	if (magic_nbr == MH_MAGIC_64)
		return (nm_magic_64(data));
	else if (magic_nbr == FAT_MAGIC || magic_nbr == FAT_CIGAM)
		return (nm_fat(data));
	else if (!ft_strncmp(data, ARMAG, SARMAG))
		return (nm_archive(data, file));
	return (nm_error("Unknow format file", file));
}
