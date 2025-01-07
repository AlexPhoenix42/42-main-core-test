/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:15:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 18:49:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

size_t			hex_printf(va_list args, t_printf_form *form_found,
					char *flags, char **str);

static size_t	hex_printf_frame(t_printf_form *form_found, char *flags,
					unsigned int ux, size_t hex_len);
static size_t	hex_printf_frame0(t_printf_form *form_found, char *flags,
					unsigned int ux, size_t hex_len);
static size_t	hex_printf_logic(t_printf_form *form_found, size_t hex_len,
					char *flags, unsigned int ux);
static size_t	hex_printf_prefix(t_printf_form *form_found, size_t hex_len,
					char *flags, unsigned int ux);

// when ux == 0 the whole width should
// be printed as 'space' including the position of '0'.
size_t	hex_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str)
{
	unsigned int	ux;
	size_t			hex_len;
	size_t			len_r;

	ux = va_arg(args, unsigned int);
	len_r = 0;
	if (ux == 0)
		hex_len = 0;
	else
		hex_len = hex_len_uint(ux);
	form_found->i = -1;
	len_r = hex_printf_frame(form_found, flags, ux, hex_len);
	if (form_found->form == 'x')
		*str = ft_strchr((const char *)(*str), (int) 'x') + 1;
	else
		*str = ft_strchr((const char *)(*str), (int) 'X') + 1;
	return (len_r);
}

static size_t	hex_printf_frame(t_printf_form *form_found, char *flags,
					unsigned int ux, size_t hex_len)
{
	size_t	len_r;

	len_r = 0;
	if (flags[5] == '.' || form_found->width != 0)
		len_r += hex_printf_frame0(form_found, flags, ux, hex_len);
	else
		len_r += hex_printf_logic(form_found, hex_len, flags, ux);
	return (len_r);
}

static size_t	hex_printf_frame0(t_printf_form *form_found, char *flags,
					unsigned int ux, size_t hex_len)
{
	size_t	len_r;
	char	b;

	len_r = 0;
	b = (2 * (((flags[4]) / '#') & (ux != 0)));
	if (flags[5] == '.' && form_found->precision <= hex_len)
	{
		if (form_found->width > hex_len && flags[0] != '-' && form_found->width
			> hex_len + b)
			while (++(form_found->i) < form_found->width - hex_len - b)
				len_r += write(1, " ", 1);
		len_r += hex_printf_logic(form_found, hex_len, flags, ux);
	}
	else if (flags[5] == '.' && form_found->precision > hex_len)
	{
		if (form_found->width > form_found->precision && flags[0] != '-'
			&& form_found->width > hex_len + b)
			while (++(form_found->i) < form_found->width
				- form_found->precision - b)
				len_r += write(1, " ", 1);
		len_r += hex_printf_logic(form_found, hex_len, flags, ux);
	}
	else
		len_r += hex_printf_logic(form_found, hex_len, flags, ux);
	return (len_r);
}

static size_t	hex_printf_logic(t_printf_form *form_found, size_t hex_len,
					char *flags, unsigned int ux)
{
	size_t	len_r;

	form_found->i = -1;
	if (form_found->form == 'X')
		form_found->hex_ox[1] = 'X';
	len_r = hex_printf_prefix(form_found, hex_len, flags, ux);
	if (ux != 0)
		wint2hex(ux, (form_found->form) / 'X', 0);
	if (form_found->width > hex_len && flags[0] == '-')
		len_r += hex_printf_logic_cnd(form_found, hex_len, flags, ux);
	if (ux != 0)
		len_r += hex_len;
	return (len_r);
}

static size_t	hex_printf_prefix(t_printf_form *form_found, size_t hex_len,
					char *flags, unsigned int ux)
{
	size_t	len_r;

	len_r = 0;
	if (flags[5] != '.')
		len_r += hex_printf_prefix_cnd(form_found, hex_len, flags, ux);
	if (flags[5] == '.')
	{
		if (flags[4] == '#' && ux != 0)
			len_r += write(1, form_found->hex_ox, 2);
		if (form_found->precision > hex_len)
			while (++(form_found->i) < form_found->precision - hex_len)
				len_r += write(1, "0", 1);
	}
	return (len_r);
}
