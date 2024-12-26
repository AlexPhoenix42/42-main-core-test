/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_len_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:44:32 by codespace         #+#    #+#             */
/*   Updated: 2024/12/11 07:37:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

// Calculats the hexadicimal lengh of a pointer
size_t	hex_len_pointer(void *ptr)
{
	size_t	i;
	uintptr_t	address;

	i = 0;
	address = (uintptr_t) ptr;
	if (!ptr)
		return (0);
	else
		while (address != 0 && ++i > 0)
			address /= 16;
	return (i);
}

// Calculats the hexadicimal lengh of an unsigned int
size_t	hex_len_uint(unsigned int ux)
{
	size_t	i;

	i = 0;
	if (ux == 0)
		return (1);
	else
		while (ux != 0 && ++i > 0)
			ux /= 16;
	return (i);
}
