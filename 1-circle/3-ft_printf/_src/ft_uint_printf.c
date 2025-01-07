/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:20:33 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 19:18:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

size_t			uint_printf(va_list args, t_printf_form *form_found,
					char *flags, char **str);

static size_t	uint_printf_logic0(t_printf_form *form_found, char *flags,
					unsigned int ux, size_t uint_len);
static size_t	uint_printf_logic(t_printf_form *form_found, char *flags,
					unsigned int ux, size_t uint_len);
static size_t	uint_printf_logic_prefix(t_printf_form *form_found,
					char *flags, size_t uint_len);

size_t	uint_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str)
{
	unsigned int	ux;
	size_t			uint_len;
	size_t			len_r;

	len_r = 0;
	ux = va_arg(args, unsigned int);
	uint_len = getintlen(ux);
	if (flags[5] == '.' || form_found->width != 0)
		len_r += uint_printf_logic0(form_found, flags, ux, uint_len);
	else
		len_r += uint_printf_logic(form_found, flags, ux, uint_len);
	*str = ft_strchr((const char *)(*str), (int) 'u') + 1;
	return (len_r);
}

static size_t	uint_printf_logic0(t_printf_form *form_found, char *flags,
							unsigned int ux, size_t uint_len)
{
	size_t	len_r;
	size_t	j;

	len_r = 0;
	j = -1;
	if (flags[5] == '.' && form_found->precision <= uint_len)
	{
		if (form_found->width > uint_len && flags[0] != '-')
			while (++j < form_found->width - uint_len)
				len_r += write(1, " ", 1);
		len_r += uint_printf_logic(form_found, flags, ux, uint_len);
	}
	else if (flags[5] == '.' && form_found->precision > uint_len)
	{
		if (form_found->width > form_found->precision && flags[0] != '-')
			while (++j < form_found->width - form_found->precision)
				len_r += write(1, " ", 1);
		len_r += uint_printf_logic(form_found, flags, ux, uint_len);
	}
	else
		len_r += uint_printf_logic(form_found, flags, ux, uint_len);
	return (len_r);
}

static size_t	uint_printf_logic(t_printf_form *form_found, char *flags,
							unsigned int ux, size_t uint_len)
{
	size_t	j;
	size_t	len_r;
	char	b;

	len_r = 0;
	b = form_found->precision == 0;
	len_r = uint_printf_logic_prefix(form_found, flags, uint_len);
	if (ux != 0)
		len_r += wuint2base(ux, "0123456789", 10);
	else if (b && form_found->width == 0 && flags[5] == '.')
		len_r += write(1, "", 1);
	else if (b && form_found->width != 0 && flags[5] == '.')
		len_r += write(1, " ", 1);
	else
		len_r += write(1, "0", 1);
	j = -1;
	if (form_found->width > uint_len && flags[0] == '-')
		while (++j < form_found->width - uint_len)
			len_r += write(1, " ", 1);
	return (len_r);
}

static size_t	uint_printf_logic_prefix(t_printf_form *form_found,
					char *flags, size_t uint_len)
{
	size_t	len_r;
	size_t	j;

	len_r = 0;
	j = -1;
	if (flags[5] != '.' && flags[0] != '-' && form_found->width >= uint_len)
		if (flags[2] != '0' && form_found->width)
			while (++j < form_found->width - uint_len
				&& form_found->width >= uint_len)
				len_r += write(1, " ", 1);
	if (flags[5] == '.' && form_found->precision > uint_len)
		while (++j < form_found->precision - uint_len)
			len_r += write(1, "0", 1);
	if (flags[5] != '.' && flags[0] != '-'
		&& (form_found->width >= uint_len || !form_found->width))
	{
		j = -1;
		if (flags[2] == '0' && form_found->width)
			while ((!++j && form_found->width)
				|| j < form_found->width - uint_len)
				len_r += write(1, "0", 1);
	}
	return (len_r);
}
