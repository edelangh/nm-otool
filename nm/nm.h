/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:04:41 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/28 14:35:31 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

#include <mach-o/ranlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <ar.h>

typedef struct stat			t_stat;

typedef struct				s_section
{
	char					*name;
	unsigned int			nb;
	struct s_section		*next;
}							t_section;

typedef struct				s_lsection
{
	t_section				*first;
	t_section				*last;
}							t_lsection;

typedef struct				s_memlist
{
	size_t					value;
	char					type;
	char					*str;
	struct s_memlist		*next;
	struct s_memlist		*prev;
}							t_memlist;

int			nm_error(const char *s, const char *arg);

int			nm(const char *path);
int			parse_file(const char *data, const char *file);

int			nm_magic_64(const char *data);

t_lsection	*get_sections(struct load_command *c, struct mach_header_64 *m);

int			nm_sym(
	struct symtab_command* command,
	const char *data,
	t_lsection *sections);

t_memlist	*add_elem(
	t_memlist *elem,
	struct nlist_64 list,
	char *strtable,
	t_lsection *sec);
#endif
