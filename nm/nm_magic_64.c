/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_magic_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 15:12:39 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 16:10:00 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	nm_magic_64(const char *data)
{
	dprintf(1, "HEY\n");
	return (0);
}

int	nm_fat(const char *data)
{
	exit(dprintf(1, "I'm a fat file ! KILL Me or implement me\n"));
	return (0);
}
