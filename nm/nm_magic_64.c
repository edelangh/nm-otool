/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_magic_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 15:12:39 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 19:35:08 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "nm.h"

int	nm_magic_64(const char *data)
{
	struct mach_header_64	*header;
	struct load_command		*command;
	t_lsection				*sections;
	unsigned int			i;
	unsigned int			count;

	header = (struct mach_header_64*)data;
	count = header->ncmds;
	command = (struct load_command*)(data + sizeof(struct mach_header_64));
	sections = get_sections(command, header);
	i = 0;
	while (i < count)
	{
		if (command->cmd == LC_SYMTAB)
		{
			nm_sym((struct symtab_command*)command, data, sections);
		}
		command = (struct load_command*)((char*)command + command->cmdsize);
		++i;
	}
	return (0);
}
