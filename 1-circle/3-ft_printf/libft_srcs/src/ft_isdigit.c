/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:21:25 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 17:21:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	unsigned char	uc;

	if (c == EOF)
		return (0);
	uc = (unsigned char) c;
	if ('0' <= uc && uc <= '9')
		return (1);
	return (0);
}
