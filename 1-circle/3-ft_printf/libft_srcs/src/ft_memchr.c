/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:13:34 by codespace         #+#    #+#             */
/*   Updated: 2024/12/26 15:57:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_memchr(char *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (((unsigned char *) s)[i] == (unsigned char) c)
			return (s + i);
	return (NULL);
}
