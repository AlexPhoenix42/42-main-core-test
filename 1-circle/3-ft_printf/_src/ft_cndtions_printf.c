/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cndtions_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:20:34 by codespace         #+#    #+#             */
/*   Updated: 2024/12/29 16:09:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include <stdlib.h>
#include <unistd.h>

// size_t	hex_printf_prefix_cnd(t_printf_form *form_found, size_t hex_len,
// 			char *flags, unsigned int ux);
// size_t	hex_printf_logic_cnd(t_printf_form *form_found, size_t hex_len,
// 			char *flags, unsigned int ux);
// size_t	int_printf_logic_prefix0_cnd(t_printf_form *form_found, size_t int_len,
// 			char *flags, int x);

// hex_printf_prefix() condition without '.' flag
size_t	hex_printf_prefix_cnd(t_printf_form *form_found, size_t hex_len,
			char *flags, unsigned int ux)
{
	size_t	len_r;
	char	b;

	len_r = 0;
	b = (2 * (((flags[4]) / '#') & (ux != 0)));
	if (form_found->width > hex_len + b)
		if (flags[2] != '0' && flags[0] != '-'
			&& form_found->width >= hex_len)
			while (++(form_found->i) < form_found->width - hex_len - b)
				len_r += write(1, " ", 1);
	if (flags[4] == '#' && ux != 0)
		len_r += write(1, form_found->hex_ox, 2);
	if (form_found->width > hex_len + b)
		if (flags[2] == '0' && form_found->width >= hex_len)
			while (++(form_found->i) < form_found->width - hex_len - b)
				len_r += write(1, "0", 1);
	return (len_r);
}

size_t	hex_printf_logic_cnd(t_printf_form *form_found, size_t hex_len,
			char *flags, unsigned int ux)
{
	size_t	j;
	size_t	len_r;
	char	b;

	j = -1;
	b = (2 * (((flags[4]) / '#') & (ux != 0)));
	if (form_found->precision <= hex_len
		&& form_found->width > hex_len + b)
		while (++j < form_found->width - hex_len - b)
			len_r += write(1, " ", 1);
	else if (form_found->precision > hex_len
		&& form_found->width > hex_len + b)
		while (++j < form_found->width - form_found->precision - b)
			len_r += write(1, " ", 1);
	return (len_r);
}

size_t	int_printf_logic_prefix0_cnd(t_printf_form *form_found, size_t int_len,
			char *flags, int x)
{
	size_t	j;
	size_t	len_r;
	char	logic;
	char	logic2;

	logic = 0;
	len_r = 0;
	logic = ((flags[3] / ' ') & (!(flags[2] / '0')))
		| ((flags[3] / ' ') & (flags[2] / '0'));
	logic2 = (logic & (flags[1] != '+')) & ((logic & (x >= 0)));
	if (logic2 && x > 0 && flags[1] != '+' && flags[2] != '0')
		len_r += write(1, " ", 1);
	j = -1;
	while ((logic2) && ++j < form_found->width - int_len
		- ((x < 0) | flags[1] / '+' | flags[3] / ' ')
		&& form_found->width >= int_len)
		len_r += write(1, " ", 1);
	j = -1;
	if (!logic2 && form_found->width && flags[2] != '0')
		while (++j < form_found->width - int_len - ((x < 0)
				| flags[1] / '+') && form_found->width >= int_len)
			len_r += write(1, " ", 1);
	return (len_r);
}
