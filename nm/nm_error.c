/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:36:55 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 14:38:42 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

int	nm_error(const char *s, const char *arg)
{
	write(2, s, ft_strlen(s));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
	return (1);
}
