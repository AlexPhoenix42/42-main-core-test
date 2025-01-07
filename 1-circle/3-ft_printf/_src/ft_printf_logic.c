/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:32:37 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 19:17:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_lib.h"
#include <errno.h>

int			ft_printf_logic(char *str, va_list args);

static void	init_printf_form(t_printf_form *form_found, char *is_found);
static void	get_form(char *str, char *flags, char *forms,
			t_printf_form *form_found);
static void	get_form_logic(char *str, char *flags,
			char *forms, t_printf_form *form_found);
static void	check_form_logic(size_t i, char *str,
			char *flags, t_printf_form *form_found);

int	ft_printf_logic(char *str, va_list args)
{
	size_t			len_r;
	char			*ptr;
	t_printf_form	form_found;

	len_r = 0;
	init_printf_form(&form_found, NULL);
	form_found.is_found = ft_print_char(str, &ptr, &len_r, -1);
	while (form_found.is_found)
	{
		get_form(ptr + 1, "-0#. +", "cspdiuxX%", &form_found);
		if (!(process_arg(args, &ptr, &form_found, &len_r)) || errno)
			return (-1);
		if (form_found.is_found)
		{
			if (form_found.form != '%')
				while (ft_memchr("cspdiuxX", *ptr, 8) != NULL)
					++ptr;
			init_printf_form(&form_found, NULL);
		}
		if (errno)
			return (-1);
		form_found.is_found = ft_print_char(ptr, &ptr, &len_r, -1);
	}
	return ((int) len_r);
}

static void	init_printf_form(t_printf_form *form_found, char *is_found)
{
	form_found->i = -1;
	form_found->is_found = is_found;
	ft_memcpy(form_found->flags, (char []){1, 1, 1, 1, 1, 0}, 6);
	form_found->form = '\0';
	form_found->width = 0;
	form_found->precision = 0;
	form_found->widthc = NULL;
	form_found->precisionc = NULL;
	form_found->hex_ox[0] = '0';
	form_found->hex_ox[1] = 'x';
	form_found->hex_ox[2] = '\0';
}

static void	get_form(char *str, char *flags,
				char *forms, t_printf_form *form_found)
{
	if (!str || !flags || !forms || !form_found)
		return ;
	if (ft_memchr(forms, str[0], 9) != NULL)
		form_found->form = str[0];
	else
		get_form_logic(str, flags, forms, form_found);
}

static void	get_form_logic(char *str, char *flags,
				char *forms, t_printf_form *form_found)
{
	size_t	i;

	i = -1;
	form_found->i = -1;
	while ((ft_memchr(flags, str[++i], 6) != NULL) || ft_isdigit_pls(str[i]))
	{
		check_form_logic(i, str, flags, form_found);
		if ((ft_memchr(forms, str[i + 1], 9) != NULL))
		{
			form_found->form = str[i + 1];
			if (form_found->widthc)
				form_found->width = string2int(form_found->widthc, 1);
			if (form_found->precisionc)
				form_found->precision
					= string2int((form_found->precisionc) + 1, 1);
			break ;
		}
		if ((form_found->widthc || form_found->precisionc)
			&& ft_isdigit(str[i]) && !ft_isdigit(str[i + 1]))
			if (form_found->widthc && str[i + 1] != '.' )
				break ;
	}
}

static void	check_form_logic(size_t i, char *str,
							char *flags, t_printf_form *form_found)
{
	if (++(form_found->i) < 6 && (ft_memchr(flags, str[i], 6) != NULL)
		&& ft_memchr(form_found->flags, str[i], 6) == NULL)
	{
		if (str[i] != '0')
			(form_found->flags)[(form_found->i)] = str[i];
		else if (!(form_found->widthc))
			(form_found->flags)[(form_found->i)] = str[i];
	}
	if (!(form_found->widthc) && str[i - 1] != '.'
		&& !ft_isdigit_pls(str[i - 1]) && ft_isdigit_pls(str[i]))
		form_found->widthc = str + i;
	if (!(form_found->precisionc) && str[i] == '.')
		form_found->precisionc = &(str[i]);
}
