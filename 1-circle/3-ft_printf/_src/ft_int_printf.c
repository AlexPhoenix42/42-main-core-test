/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:56:32 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 18:49:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

size_t			int_printf(va_list args, t_printf_form *form_found,
					char *flags, char **str);

static size_t	int_printf_logic0(t_printf_form *form_found, size_t int_len,
					char *flags, int x);
static size_t	int_printf_logic(t_printf_form *form_found, size_t int_len,
					char *flags, int x);
static size_t	int_printf_logic_prefix(t_printf_form *form_found,
					size_t int_len, char *flags, int x);
static size_t	int_printf_logic_prefix0(t_printf_form *form_found,
					size_t int_len, char *flags, int x);

size_t	int_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str)
{
	int		x;
	size_t	int_len;
	size_t	len_r;

	x = va_arg(args, int);
	int_len = getintlen(x);
	len_r = 0;
	if (flags[5] == '.' || form_found->width != 0)
		len_r += int_printf_logic0(form_found, int_len, flags, x);
	else
	{
		if (flags[3] == ' ' && x >= 0 && flags[1] != '+'
			&& (form_found->width >= int_len || !form_found->width))
			len_r += write(1, " ", 1);
		len_r += int_printf_logic(form_found, int_len, flags, x);
	}
	if (form_found->form == 'd')
		*str = ft_strchr((const char *)(*str), (int) 'd') + 1;
	else
		*str = ft_strchr((const char *)(*str), (int) 'i') + 1;
	return (len_r);
}

static size_t	int_printf_logic0(t_printf_form *frm_fnd, size_t int_len,
					char *flags, int x)
{
	size_t	len_r;
	size_t	j;

	len_r = 0;
	j = -1;
	frm_fnd->boolen = ((x < 0) | flags[1] / '+');
	if (flags[5] == '.' && frm_fnd->precision <= int_len)
	{
		if (frm_fnd->width <= int_len && flags[1] != '+' && flags[3] == ' ')
			len_r += write(1, " ", 1);
		if (frm_fnd->width > int_len && flags[0] != '-')
			while (++j < frm_fnd->width - int_len - frm_fnd->boolen)
				len_r += write(1, " ", 1);
		len_r += int_printf_logic(frm_fnd, int_len, flags, x);
	}
	else if (flags[5] == '.' && frm_fnd->precision > int_len)
	{
		if (frm_fnd->width > frm_fnd->precision && flags[0] != '-')
			while (++j < frm_fnd->width - frm_fnd->precision - frm_fnd->boolen)
				len_r += write(1, " ", 1);
		len_r += int_printf_logic(frm_fnd, int_len, flags, x);
	}
	else
		len_r += int_printf_logic(frm_fnd, int_len, flags, x);
	return (len_r);
}

static size_t	int_printf_logic(t_printf_form *form_found, size_t int_len,
					char *flags, int x)
{
	size_t	j;
	size_t	len_r;

	len_r = 0;
	len_r += int_printf_logic_prefix(form_found, int_len, flags, x);
	if (x != 0)
		len_r += wint2base_minus(x, "0123456789", 10);
	else if (form_found->precision == 0 && form_found->width == 0
		&& flags[5] == '.')
		len_r += write(1, "", 1);
	else if (form_found->precision == 0 && form_found->width != 0
		&& flags[5] == '.')
		len_r += write(1, " ", 1);
	else
		len_r += write(1, "0", 1);
	j = -1;
	if (form_found->width > int_len && flags[0] == '-')
		while (++j < form_found->width - int_len - ((x < 0) | flags[1] / '+'))
			len_r += write(1, " ", 1);
	return (len_r);
}

static size_t	int_printf_logic_prefix(t_printf_form *form_found,
					size_t int_len, char *flags, int x)
{
	size_t	j;
	size_t	len_r;

	len_r = 0;
	j = -1;
	len_r += int_printf_logic_prefix0(form_found, int_len, flags, x);
	if (x < 0)
		len_r += write(1, "-", 1);
	if (x >= 0 && flags[1] == '+')
		len_r += write(1, "+", 1);
	if (flags[5] == '.' && form_found->precision > int_len)
	{
		if (flags[1] != '+' && flags[3] == ' ')
			len_r += write(1, " ", 1);
		while (++j < form_found->precision - int_len)
			len_r += write(1, "0", 1);
	}
	if (flags[5] != '.' && flags[0] != '-' && (form_found->width >= int_len
			|| !form_found->width))
		if (flags[2] == '0' && form_found->width)
			while ((!++j && form_found->width) || j < form_found->width
				- int_len - ((x < 0) | flags[1] / '+' | flags[3] / ' '))
				len_r += write(1, "0", 1);
	return (len_r);
}

static size_t	int_printf_logic_prefix0(t_printf_form *form_found,
					size_t int_len, char *flags, int x)
{
	size_t	len_r;

	len_r = 0;
	if (flags[5] != '.' && flags[0] != '-' && form_found->width >= int_len)
		len_r += int_printf_logic_prefix0_cnd(form_found, int_len, flags, x);
	return (len_r);
}
