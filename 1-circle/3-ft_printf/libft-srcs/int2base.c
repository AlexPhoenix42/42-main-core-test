/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int2base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:40:10 by codespace         #+#    #+#             */
/*   Updated: 2024/12/11 07:59:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	wint2base(int nbr, char *base, unsigned int baselen)
{
	int q;
	int r;
	int c;
	size_t	len_r;

	len_r = 0;
	if (nbr == -2147483647 || nbr < 0)
	{
		nbr = -nbr;
		write(1, "-", 1);
	}
	q = nbr;
	if (q != 0)
	{
		wint2base((q / baselen), base, baselen);
		r = q % baselen;
		c = base[r];
		len_r += write(1, &c, 1);
	}
	return (len_r);
}

// This will not print '-' for INT_MIN
// This is used for ft_printf()
size_t	wint2base_minus(int nbr, char *base, unsigned int baselen)
{
	int q;
	int r;
	int c;
	size_t	len_r;

	len_r = 0;
	if (nbr == -2147483647 || nbr < 0)
	{
		nbr = -nbr;
		// write(1, "-", 1);
	}
	q = nbr;
	if (q != 0)
	{
		wint2base_minus((q / baselen), base, baselen);
		r = q % baselen;
		c = base[r];
		len_r += write(1, &c, 1);
	}
	return (len_r);
}

static size_t	wuint2base(unsigned int nbr, char *base, unsigned int baselen)
{
	unsigned int q;
	unsigned int r;
	int c;
	size_t	len_r;

	len_r = 0;
	q = nbr;
	if (q != 0)
	{
		wint2base_minus((q / baselen), base, baselen);
		r = q % baselen;
		c = base[r];
		len_r += write(1, &c, 1);
	}
	return (len_r);
}

void	wint2hex(int nbr, char upper, size_t position)
{
	size_t	i;
	int q;
	int r;
	char c;
	char base[16];

	// base = "0123456789abcdef";
	i = -1;
	while (++i < 16)
		if (i < 10)
			base[i] = 48 + i;
		else
			base[i] = 87 + i;
	q = nbr;
	if (q != 0)
	{
		wint2hex((q / 16), upper, (position + 1));
		r = q % 16;
		c = base[r];
		if (!ft_isdigit(c) && upper == 1)
			c = c - 32;
		// hexnb[(hexnblen - 1) - position] = c;
		write(1, &c, 1);
	}
	// return (i);
}


