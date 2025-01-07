/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:10:58 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 17:12:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	string2int(char *str, int sign);

int	string2int(char *str, int sign)
{
	size_t	i;
	long	x;

	if (!str)
		return (0);
	x = 0;
	i = -1;
	while ('0' <= str[++i] && str[i] <= '9')
	{
		x = (x * 10) + (str[i] - '0');
		if (x >= INT_MAX)
			return (INT_MAX);
		if (x <= INT_MIN)
			return (INT_MIN);
	}
	return (x * sign);
}
