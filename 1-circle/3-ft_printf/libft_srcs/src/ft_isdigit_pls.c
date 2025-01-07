/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_pls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:20:00 by codespace         #+#    #+#             */
/*   Updated: 2024/12/10 17:22:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isdigit_pls(int c)
{
	unsigned char	uc;

	if (c == EOF)
		return (0);
	uc = (unsigned char) c;
	if ('1' <= uc && uc <= '9')
		return (1);
	return (0);
}
