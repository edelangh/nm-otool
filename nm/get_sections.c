/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 18:10:30 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 19:32:05 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <libft.h>
#include <stdlib.h>

static void		add_lst(char *name, t_lsection *lst)
{
	t_section	*add;

	if ((add = (t_section*)malloc(sizeof(t_section))) == NULL)
		return ;
	add->name = name;
	add->next = NULL;
	if (lst->first == NULL)
	{
		lst->first = add;
		lst->last = add;
		add->nb = 1;
	}
	else
	{
		add->nb = lst->last->nb + 1;
		lst->last->next = add;
		lst->last = add;
	}
}

static void		add_segment(struct load_command *com, t_lsection *lst)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)com;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		add_lst(sec->sectname, lst);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

t_lsection		*get_sections(struct load_command *c, struct mach_header_64 *m)
{
	t_lsection		*lst;
	unsigned int	i;

	i = 0;
	if ((lst = (t_lsection*)ft_memalloc(sizeof(t_lsection))) == NULL)
		return (NULL);
	while (i < m->ncmds)
	{
		if (c->cmd == LC_SEGMENT_64)
			add_segment(c, lst);
		c += c->cmdsize / sizeof(void*);
		i++;
	}
	return (lst);
}
