/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:04:50 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 18:50:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int	process_arg(va_list args, char **str,
	t_printf_form *form_found, size_t *len_r);
	
static void	set_processed_flags(t_printf_form *form_found, char *flags);

int	process_arg(va_list args, char **str,
	t_printf_form *form_found, size_t *len_r)
{
	char	flags[7];

	ft_memcpy(flags, (char []){0, 0, 0, 0, 0, 0, 0}, 7);
	set_processed_flags(form_found, flags);
	if (form_found->form == '%')
	{
		*len_r += write(1, "%", 1);
		*str = ft_strchr((const char *)(*str) + 1, (int) '%') + 1;
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

static void	set_processed_flags(t_printf_form *form_found, char *flags)
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
