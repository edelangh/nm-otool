/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:04:41 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 15:14:10 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

typedef struct stat		t_stat;

int		nm_error(const char *s, const char *arg);

int		nm(const char *path);
int		parse_file(const char *data, const char *file);

int		nm_magic_64(const char *data);
int		nm_fat(const char *data);
#endif
