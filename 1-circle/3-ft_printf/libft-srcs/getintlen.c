/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getintlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:26:34 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 17:26:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	getintlen(signed long long int x)
{
	size_t	i;

	i = 0;
	if (x == 0)
	{
		i = 1;
		return (i);
	}
	while (x != 0)
	{
		i++;
		x /= 10;
	}
	return (i);
}
