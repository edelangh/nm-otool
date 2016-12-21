/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:06:57 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 15:30:29 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int		nm(const char *path)
{
	int		fd;
	char	*data;
	t_stat	stat;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (nm_error("Counld not open file:", path));
	if (fstat(fd, &stat) < 0)
		return (nm_error("Could not fstat file:", path));
	if ((data = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == NULL)
		exit (nm_error("Could not mmap file:", path));
	parse_file(data, path);
	if (munmap(data, stat.st_size) < 0)
		exit (nm_error("Could not munmap file:", path));
	return (0);
}
