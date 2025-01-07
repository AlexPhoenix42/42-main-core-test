/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getptradrs2hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:55:02 by codespace         #+#    #+#             */
/*   Updated: 2024/12/26 15:54:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdint.h>

void	getptradrs2hex(uintptr_t nbr, size_t position);

void	getptradrs2hex(uintptr_t nbr, size_t position)
{
	size_t		i;
	uintptr_t	q;
	uintptr_t	r;
	char		c;
	char		base[16];

	i = -1;
	while (++i < 16)
		if (i < 10)
			base[i] = 48 + i;
		else
			base[i] = 87 + i;
	q = nbr;
	if (q != 0)
	{
		getptradrs2hex((q / 16), (position + 1));
		r = q % 16;
		c = base[r];
		write(1, &c, 1);
	}
}
