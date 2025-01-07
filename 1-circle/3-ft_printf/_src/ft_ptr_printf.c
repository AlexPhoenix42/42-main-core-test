/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:12:25 by codespace         #+#    #+#             */
/*   Updated: 2024/12/29 16:11:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>

// size_t			ptr_printf(va_list args, t_printf_form *form_found,
// 					char *flags, char **str);
static size_t	ptr_printf_logic(void *p, t_printf_form *form_found,
					char *flags, size_t hex_len);
static size_t	ptr_printf_logic_prefix(void *p, t_printf_form *form_found,
					char *flags, size_t hex_len);

size_t	ptr_printf(va_list args, t_printf_form *form_found,
			char *flags, char **str)
{
	void	*p;
	size_t	hex_len;
	size_t	j;
	size_t	i;
	size_t	len_r;

	p = va_arg(args, void *);
	j = -1;
	i = 0;
	len_r = 0;
	hex_len = hex_len_pointer(p);
	if (p)
		i = 2;
	else
		hex_len = 5;
	len_r += ptr_printf_logic(p, form_found, flags, hex_len);
	if (flags[0] == '-' && form_found->width > hex_len)
		while (++j < form_found->width - hex_len - i)
			len_r += write(1, " ", 1);
	len_r += hex_len;
	*str = ft_strchr((const char *)(*str), (int) 'p') + 1;
	return (len_r);
}

static size_t	ptr_printf_logic(void *p, t_printf_form *form_found,
					char *flags, size_t hex_len)
{
	size_t	len_r;

	len_r = 0;
	ptr_printf_logic_prefix(p, form_found, flags, hex_len);
	if (p)
	{
		if (flags[2] != '0' || form_found->width < hex_len)
			len_r += write(1, "0x", 2);
		getptradrs2hex((uintptr_t) p, 0);
	}
	else
		write(1, "(nil)", 5);
	return (len_r);
}

static size_t	ptr_printf_logic_prefix(void *p, t_printf_form *form_found,
					char *flags, size_t hex_len)
{
	size_t	i;
	size_t	j;
	size_t	len_r;

	j = -1;
	len_r = 0;
	i = 0;
	if (p)
		i = 2;
	if (flags[0] != '-' && form_found->width > hex_len)
	{
		if (flags[2] == '0' && p)
		{
			len_r += write(1, "0x", 2);
			while (++j < form_found->width - hex_len - i)
				len_r += write(1, "0", 1);
		}
		else if (flags[2] != '0' || (flags[2] == '0' && !p))
			while (++j < form_found->width - hex_len - i)
				len_r += write(1, " ", 1);
	}
	return (len_r);
}
