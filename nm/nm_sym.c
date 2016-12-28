/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sym.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 19:09:26 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/28 14:36:04 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <libft.h>
#include <ft_printf.h>

#define false 0
#define true 1

static void				display_nm(size_t value, char type, char *str, int isgot)
{
	char *tmp;

	if (isgot) {
		tmp = ft_strdup("                ");
	}
	else
		ft_asprintf(&tmp, "%016llx", value);
	ft_printf("%s %c %s\n", tmp, type, str);
	free(tmp);
}

static void				aff_elem(t_memlist *elem)
{
	t_memlist	*tmp;

	tmp = elem;
	while (tmp)
	{
		if (tmp->value)
			display_nm(tmp->value, tmp->type, tmp->str, false);
		else if (ft_strcmp(&tmp->type, "U") == 0)
			display_nm(0, tmp->type, tmp->str, true);
		else
			display_nm(0, tmp->type, tmp->str, false);
		tmp = tmp->next;
	}
}

static t_memlist		*del_elem(t_memlist *elem)
{
	t_memlist			*tmp;
	t_memlist			*tmp2;

	tmp = elem;
	while (tmp)
	{
		if ((tmp->type == 'z' || tmp->type == 'Z') ||\
				(tmp->next && tmp->value && tmp->value == tmp->next->value))
		{
			if (tmp->type != 'z' && tmp->type != 'Z' && tmp->next->type == '?')
				tmp = tmp->next;
			tmp2 = tmp->next;
			if (tmp2)
				tmp2->prev = tmp->prev;
			tmp->prev->next = tmp2;
			free(tmp->str);
			free(tmp);
		}
		tmp = tmp->next;
	}
	return (elem);
}

int		nm_sym(
		struct symtab_command* command,
		const char *data,
		t_lsection *sections)
{
	int					i;
	char				*strtable;
	struct nlist_64		*list;
	t_memlist			*elem;

	i = 0;
	list = (void *)data + command->symoff;
	elem = NULL;
	strtable = (void *)data + command->stroff;
	while (i < (int)command->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0
				&& strtable + list[i].n_un.n_strx && ft_strlen(strtable +\
					list[i].n_un.n_strx) && list[i].n_type != 100)
		{
			elem = add_elem(elem, list[i], strtable, sections);
		}
		i++;
	}
	elem = del_elem(elem);
	aff_elem(elem);
	return (0);
}
