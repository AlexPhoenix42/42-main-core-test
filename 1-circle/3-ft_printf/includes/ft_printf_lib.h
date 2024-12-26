/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:40:31 by codespace         #+#    #+#             */
/*   Updated: 2024/12/14 16:42:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdarg.h>

static int		ft_printf_logic(char *str, va_list args);
static void		init_printf_form(printf_form *form_found, char *is_found);
static void		get_form(char *str, char *flags, char *forms,
						printf_form *form_found);
static void		get_form_logic(char *str, char *flags, char *forms,
					printf_form *form_found);
static void		check_form_logic(size_t i, char *str, char *flags,
					printf_form *form_found);

size_t	char_printf(va_list args, printf_form *form_found,
			char *flags, char **str);
size_t	str_printf(va_list args, printf_form *form_found,
			char *flags, char **str);




typedef struct	form_found
{
	size_t	i;
	char	*is_found;
	char	flags[6];
	char	form;
	char	*widthc;
	char	*precisionc;
	char	hex_ox[3];
	char	boolen;
	size_t	width;
	size_t	precision;
} printf_form;
