/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:32:14 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 16:51:54 by edelangh         ###   ########.fr       */
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

static int	nm_archive(const char *data, const char *file)
{
	struct ar_hdr		*ar;
	struct ranlib		*rans;
	unsigned int		size;
	unsigned int		count;
	unsigned int		i;

	i = 0;
	ar = (struct ar_hdr*)(data + SARMAG);
	size = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
	count = *((unsigned int*)(data + sizeof(struct ar_hdr) + SARMAG + size));
	rans = (struct ranlib*)(data + sizeof(struct ar_hdr) + SARMAG + size
								+ sizeof(unsigned int));
	count /= sizeof(struct ranlib);
	while (i < count)
	{
		if (nm_display_ranlib(rans + i, data, file) != 0)
			return (1);
		++i;
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
