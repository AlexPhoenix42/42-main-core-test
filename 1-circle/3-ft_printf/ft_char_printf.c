/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:56:19 by codespace         #+#    #+#             */
/*   Updated: 2024/12/14 13:33:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <stdlib.h>
#include <stdarg.h>

size_t		char_printf(va_list args, printf_form *form_found,
				char *flags, char **str);
size_t		str_printf(va_list args, printf_form *form_found,
				char *flags, char **str);
static char	cndbool_1(size_t *j, printf_form *form_found,
				char *flags, char *s);

size_t	char_printf(va_list args, printf_form *form_found,
			char *flags, char **str)
{
	int		c;
	char	cs[2];
	size_t	j;
	size_t	len_r;
	size_t	width;

	j = -1;
	len_r = 0;
	width = form_found->width;
	c = va_arg(args, int);
	cs[0] = (char) c;
	cs[1] = '\0';
	if (width && flags[0] == 0)
		while (++j < width - 1 && width > 0)
			len_r += write(1, ".", 1);
	ft_print_char(cs, str, &len_r, 1);
	*str = ft_strchr((const char *)(*str), (int) 'c') + 1;
	if (flags[0] == '-')
		while (++j < width - 1 && width > 0)
			len_r += write(1, ".", 1);
	return (len_r);
}

size_t	str_printf(va_list args, printf_form *form_found,
			char *flags, char **str)
{
	char	*s;
	char	cndbool[2];
	size_t	i;
	size_t	j;
	size_t	len_r;

	s = va_arg(args, char *);
	i = -1;
	j = -1;
	len_r = 0;
	if (form_found->width && flags[0] == 0)
		while (cndbool_1(&j, form_found, flags, s))
			len_r += write(1, ".", 1);
	if (form_found->form == '\0')
		ft_print_char(&(s[++i]), str, &len_r, -1);
	else if (form_found->precision != 0)
		ft_print_char(&(s[++i]), str, &len_r, form_found->precision);
	else if (flags[5] != '.' && form_found->precision == 0)
		ft_print_char(&(s[++i]), str, &len_r, ft_strlen(s));
	*str = ft_strchr((const char *)(*str), (int) 's') + 1;
	if (flags[0] == '-')
		while (++j < form_found->width + form_found->precision - ft_strlen(s))
			len_r += write(1, ".", 1);
	return (len_r);
}

// Returns the value of the condition in the comment below:
// (++j < form_found->width + form_found->precision - ft_strlen(s) &&
//  form_found->width > ft_strlen(s)) ||
// (flags[5] == '.' && form_found->precision == 0 && j < form_found->width)
static char	cndbool_1(size_t *j, printf_form *form_found,
				char *flags, char *s)
{
	size_t	slen;
	char	b1;
	char	b2;
	char	b3;

	slen = ft_strlen(s);
	b1 = 0;
	b1 = ++(*j) < form_found->width + form_found->precision - slen;
	b2 = 0;
	b2 = flags[5] == '.' && form_found->precision == 0;
	b3 = 0;
	b3 = (b1 && form_found->width > slen) || (b2 && (*j) < form_found->width);
	return (b3);
}
