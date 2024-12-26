/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_process_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:46:45 by codespace         #+#    #+#             */
/*   Updated: 2024/12/11 08:55:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static int		process_arg(va_list args, char **str, printf_form *form_found, size_t *len_r);
static void 	set_processed_flags(printf_form *form_found, char *flags);
static char		*ft_print_char(char *str, char **ptr, size_t *len_r, ssize_t n);
static char		*ft_print_char0(char *str, char **ptr, size_t *len_r, ssize_t n);

static int	process_arg(va_list args, char **str, printf_form *form_found,
				size_t *len_r)
{
	char	flags[] = {0 , 0 , 0 , 0, 0, 0, 0};

	set_processed_flags(form_found, flags);
	if (form_found->form == '%')
	{
		*len_r += write(1, "%", 1);
		*str = ft_strchr((const char*) (*str) + 1, (int) '%') + 1;
		return (1);
	}
	if (form_found->form == 'p')
		*len_r = ptr_printf(args, form_found, flags, str);
	if (form_found->form == 'x' || form_found->form == 'X')
		*len_r = hex_printf(args, form_found, flags, str);
	if (form_found->form == 'c')
		*len_r += char_printf(args, form_found, flags, str);
	if (form_found->form == 's')
		*len_r += str_printf(args, form_found, flags, str);
	if (form_found->form == 'u')
		*len_r = uint_printf(args, form_found, flags, str);
	if (form_found->form == 'd' || form_found->form == 'i')
		*len_r = int_printf(args, form_found, flags, str);
	if (form_found->form == '\0')
		ft_print_char0(*str, str, len_r, -1);
	return (1);
}

static void set_processed_flags(printf_form *form_found, char *flags)
{
	size_t	i;

	i = -1;
	while (++i < 6)
	{
		if ((form_found->flags)[i] == '-')
			flags[0] = '-';
		if ((form_found->flags)[i] == '+')
			flags[1] = '+';
		if ((form_found->flags)[i] == '0')
			flags[2] = '0';
		if ((form_found->flags)[i] == ' ')
			flags[3] = ' ';
		if ((form_found->flags)[i] == '#')
			flags[4] = '#';
		if ((form_found->flags)[i] == '.')
			flags[5] = '.';
	}
}

static char *ft_print_char(char *str, char **ptr, size_t *len_r, ssize_t n)
{
	size_t	i;
	size_t	writelen;

	errno = 0;
	writelen = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '%')
		{
			*ptr = &(str[i]);
			return (*ptr);
		}
		if (n == -1 || (n > 0 && (ssize_t) i < n))
			*len_r += write(1, &(str[i]), 1);
		if (errno)
			return (NULL);
	}
	return (NULL);
}

static char *ft_print_char0(char *str, char **ptr, size_t *len_r, ssize_t n)
{
	size_t	i;
	char	b;

	errno = 0;
	b = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '%' && b == 1)
		{
			*ptr = &(str[i]);
			return (*ptr);
		}
		b = 1;
		if (n == -1 || (n > 0 && (ssize_t) i < n))
			*len_r += write(1, &(str[i]), 1);
		if (errno)
			return (NULL);
	}
	if (str[i] == '\0')
		*ptr = &(str[i]);
	return (*ptr);
}
